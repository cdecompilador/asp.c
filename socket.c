#include "socket.h"

#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

result_tcp_socket
tcp_socket_create(ipv4_addr addr)
{
    SOCKET socket_handle = INVALID_SOCKET;

    /* Initialize WSA */
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return ERR(result_tcp_socket, message_error("Couldn't start Winsock"));
    }

    /* Create the tcp socket with r/w capabilities */
    socket_handle = WSASocketW(
            AF_INET, 
            SOCK_STREAM,
            IPPROTO_TCP,
            NULL,
            0,
            WSA_FLAG_OVERLAPPED);
    if (socket_handle == INVALID_SOCKET) {
        return ERR(result_tcp_socket, message_error("Couldn't create socket"));
    }

    return OK(result_tcp_socket, ((tcp_socket) {
            .socket_handle = socket_handle,
            .addr = addr
        })
    );
}

result_void
tcp_socket_bind(tcp_socket* self)
{
    struct sockaddr_in native_addr = ipv4_to_native(&self->addr);

    /* Bind it */
    if (bind(self->socket_handle, 
             (struct sockaddr*)&native_addr, 
             sizeof(native_addr)) == SOCKET_ERROR) {
        return ERR(result_void, message_error("Couldn't bind socket"));
    }

    return OK(result_void, NULL);
}

result_void
tcp_socket_listen(tcp_socket* self)
{
    if (listen(self->socket_handle, SOMAXCONN) == SOCKET_ERROR) {
        return ERR(result_void, message_error("Listed failed"));
    }

    return OK(result_void, NULL);
}

result_tcp_socket
tcp_socket_accept(tcp_socket* self)
{
    /* Accept the connection */
    struct sockaddr_in native_addr;
    SOCKET new_conn_handle = 
        accept(self->socket_handle, (struct sockaddr*)&native_addr, 0);
    ipv4_addr addr = ipv4_from_native(&native_addr);

    if (new_conn_handle == INVALID_SOCKET) {
        return ERR(result_tcp_socket, message_error("tcp_socket invalid socket"));
    }

    return OK(result_tcp_socket, ((tcp_socket) {
            .socket_handle = new_conn_handle,
            .addr = addr
        })
    );
}

result_void
tcp_socket_close(tcp_socket* self)
{
    if (self->socket_handle != INVALID_SOCKET) {
        closesocket(self->socket_handle);
        self->socket_handle = INVALID_SOCKET;

        return OK(result_void, NULL);
    } else {
        return ERR(result_void, message_error("Cannot close invalid socket"));
    }
}

result_void
tcp_socket_connect(tcp_socket* self)
{
    /* TODO: Handle error */
    struct sockaddr_in native_addr = ipv4_to_native(&self->addr);
    if (connect(self->socket_handle, (struct sockaddr*)&native_addr, 
                sizeof(struct sockaddr)) == SOCKET_ERROR) {
        return ERR(result_void, message_error("Socket cannot connect"));
    }

    return OK(result_void, NULL);
}

result_usize
tcp_socket_recv(tcp_socket* self, u8* buffer, usize buffer_size)
{
    i32 result = recv(self->socket_handle, (char*)buffer, buffer_size, 0);
    if (result < 0) {
        return ERR(result_usize, message_error("Tcp socket recv failed"));
    } else if (result == 0) {
        return ERR(result_usize, message_error("Connection closed on recv"));
    }

    usize bytes_returned = (usize)result;

    return OK(result_usize, bytes_returned);
}

result_usize
tcp_socket_send(tcp_socket* self, const u8* buffer, usize buffer_size)
{
    usize bytes_sent;
    i32 result = send(self->socket_handle, (const char*)buffer, buffer_size, 0);

    if (result < 0) {
        return ERR(result_usize, message_error("Tcp socket send failed"));
    } else if (result == 0) {
        return ERR(result_usize, message_error("Connection closed on send"));
    }

    bytes_sent = (usize)result;
    
    return OK(result_usize, bytes_sent);
}

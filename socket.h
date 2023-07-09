#include "ip.h"
#include "result.h"

typedef struct {
    SOCKET socket_handle;
    ipv4_addr addr;
} tcp_socket;

typedef struct {
    bool success;
    union {
        error_like error;
        tcp_socket value;
    };
} result_tcp_socket;

result_tcp_socket
tcp_socket_create(ipv4_addr addr);

result_void
tcp_socket_bind(tcp_socket* self);

result_void
tcp_socket_listen(tcp_socket* self);

result_tcp_socket
tcp_socket_accept(tcp_socket* self);

result_void
tcp_socket_close(tcp_socket* self);

result_void
tcp_socket_connect(tcp_socket* self);

result_usize
tcp_socket_recv(tcp_socket* self, u8* buffer, usize buffer_size);

result_usize
tcp_socket_send(tcp_socket* self, const u8* buffer, usize buffer_size);

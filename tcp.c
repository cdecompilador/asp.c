#include "tcp.h"

result_tcp_stream
#define WRAP(_result, _new_err) RES_WRAP(result_tcp_stream, _result, _new_err)
tcp_stream_connect(ipv4_addr addr)
{
    tcp_socket socket = WRAP(tcp_socket_create(addr), 
            message_error("Failed to create tcp_stream"));
    WRAP(tcp_socket_connect(&socket), 
            message_error("Failed to connect tcp_stream"));

    return OK(result_tcp_stream, ((tcp_stream) { .socket = socket }));
}
#undef WRAP

result_void
#define WRAP(_result, _new_err) RES_WRAP(result_void, _result, _new_err)
tcp_stream_write(tcp_stream* stream, const byte_slice* slice)
{
    usize bytes_sent = WRAP(
        tcp_socket_send(
            &stream->socket, 
            slice->buffer, slice->buffer_size),
        message_error("Writting on tcp_stream failed"));

    if (bytes_sent != slice->buffer_size) {
        printf("Error: couldn't send the full message on tcp_stream\n");
        return ERR(result_void, 
                   message_error("Couldn't send full message on tcp_stream\n"));
    }

    return OK(result_void, NULL);
}
#undef CHECK

result_void
tcp_stream_read(tcp_stream* stream, byte_slice* slice)
#define WRAP(_result, _new_err) RES_WRAP(result_void, _result, _new_err)
{
    usize bytes_read = WRAP(
        tcp_socket_recv(&stream->socket, slice->buffer, slice->buffer_size),
        message_error("Reading on tcp_stream failed")
    );

    if (bytes_read != slice->buffer_size) {
        return ERR(result_void, 
                   message_error("Couldn't recv the full message on tcp_stream"));
    }

    return OK(result_void, NULL);
}

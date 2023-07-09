#ifndef TCP_H
#define TCP_H

#include "result.h"
#include "error.h"
#include "socket.h"
#include "byte_slice.h"

typedef struct {
    tcp_socket socket;
} tcp_stream;

typedef struct {
    bool success;
    union {
        error_like error;
        tcp_stream value;
    };
} result_tcp_stream;

result_tcp_stream
tcp_stream_connect(ipv4_addr addr);

result_void
tcp_stream_write(tcp_stream* stream, const byte_slice* slice);

result_void
tcp_stream_read(tcp_stream* stream, byte_slice* slice);

typedef struct {
    tcp_socket socket;
} tcp_listener;

#endif



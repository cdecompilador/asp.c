#ifndef IP_H
#define IP_H

#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include "util.h"

typedef struct {
    u32 addr;
    u16 port;
} ipv4_addr;

inline ipv4_addr
ipv4_from(u8 addr[4], u16 port)
{  
    return (ipv4_addr) {
        .addr = *(u32*)&addr[0],
        .port = htons(port)
    };
}


inline struct sockaddr_in
ipv4_to_native(ipv4_addr* self)
{
    struct sockaddr_in addr = {0};
    addr.sin_addr.s_addr = self->addr;
    addr.sin_family = AF_INET;
    addr.sin_port = self->port;

    return addr;
}

inline ipv4_addr
ipv4_from_native(struct sockaddr_in* native_addr)
{
    return (ipv4_addr) {
        .addr = native_addr->sin_addr.s_addr,
        .port = native_addr->sin_port
    };
}

#endif

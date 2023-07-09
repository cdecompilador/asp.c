#include "net_error.h"
#include "error.h"
#include "socket.h"

int
net_error_variant(const void* _self)
{
    net_error_t* self = (net_error_t*)_self;

    return self->variant;
}

void
net_error_describe(const void* _self)
{
    net_error_t* self = (net_error_t*)_self;

    const char* variant_str;
    switch (net_error_variant(_self)) {
        case NET_ERR_INVALID_SOCKET: {
            variant_str = "INVALID_SOCKET";
        } break;
        case NET_ERR_NETWORK_DOWN: {
            variant_str = "NETWORK__DOWN";
        } break;
        case NET_ERR_CONNECTION_RESET: {
            variant_str = "CONNECTION_RESET";
        } break;
        case NET_ERR_UNKNOWN: 
        default: {
            variant_str = "UNKNOWN";
        }
    }

    CONTEXT("%s: %s", variant_str, self->message);
}

int 
infer_net_error_variant()
{
    int variant;

    switch (WSAGetLastError()) {
        case WSA_INVALID_HANDLE: { variant = NET_ERR_INVALID_SOCKET; } break;
        case WSAENETUNREACH:
        case WSAENETDOWN: { variant = NET_ERR_NETWORK_DOWN; } break;
        case WSAECONNRESET: { variant = NET_ERR_CONNECTION_RESET; } break;
        default: { variant = NET_ERR_UNKNOWN; } break;
    }

    return variant;
}

error_like
net_error(int variant, const char* message)
{
    static Error net_error_vtable = (Error) {
        .describe = net_error_describe,
        .variant = net_error_variant
    };

    static net_error_t net_error_instance = {0};
    net_error_instance.variant = variant;
    net_error_instance.message = message;

    return (error_like) {
        .self = &net_error_instance,
        .vtable = &net_error_vtable
    };
}

error_like
infer_net_error(const char* message)
{
   return net_error(infer_net_error_variant(), message);
}


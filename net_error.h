#ifndef NET_ERROR_H
#define NET_ERROR_H

#include "error.h"

enum {
    NET_ERR_INVALID_SOCKET,
    NET_ERR_NETWORK_DOWN,
    NET_ERR_CONNECTION_RESET,
    NET_ERR_UNKNOWN,
};

typedef struct {
    int variant;
    const char* message;
} net_error_t;

int
net_error_variant(const void* _self);

void
net_error_describe(const void* _self);

int 
infer_net_error_variant();

error_like
net_error(int variant, const char* message);

error_like
infer_net_error(const char* message);

#endif

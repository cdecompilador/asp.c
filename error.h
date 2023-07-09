#ifndef ERROR_H
#define ERROR_H

#include "util.h"

typedef struct {
    void (*const describe)(const void*);
    int (*const variant)(const void*);
} Error;

typedef struct {
    void* self;
    Error const* vtable;
} error_like;

inline void
error_describe(error_like err)
{
    err.vtable->describe(err.self);
}

inline int
error_variant(error_like err)
{
    return err.vtable->variant(err.self);
}

#define CONTEXT(fmt, ...) do { char* buff = malloc(MAX_ERROR_DESCRIBE_SIZE); \
    sprintf(buff, fmt, ##__VA_ARGS__); str_vec_push(&error_backtrace, buff); } while (0)

typedef struct {
    const char* message;
} message_error_t;

void
message_error_describe(const void* _self);

int
message_error_variant(const void* _self);

error_like
message_error(const char* message);

#endif

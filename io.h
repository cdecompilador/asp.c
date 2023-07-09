#ifndef IO_H
#define IO_H

#include "result.h"

typedef struct {
    result_usize (*const read)(void* self, void* buffer, usize buffer_size);
    result_usize (*const write)(void* self, const void* buffer, usize buffer_size);
} Io;

typedef struct {
    void* self;
    Io const* vtable;
} io_rw;

inline result_usize
io_read(io_rw* instance, void* buffer, usize buffer_size)
{
    return instance->vtable->read(instance->self, buffer, buffer_size);
}

inline result_usize
io_write(io_rw* instance, const void* buffer, usize buffer_size)
{
    return instance->vtable->write(instance->self, buffer, buffer_size);
}

#endif

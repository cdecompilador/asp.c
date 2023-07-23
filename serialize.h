#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "util.h"
#include "result.h"
#include "string_buffer.h"

/* Serialize interface */
typedef struct {
    /* Serialize a struct to a string_buffer */
    result_void (*const serialize)(void* self, string_buffer* buf);
} Serialize; 

typedef struct {
    void* self;
    Serialize const* vtable;
} serializable;

inline result_void
serialize(serializable* self, string_buffer* buf)
{
    return self->vtable->serialize(self->self, buf);
}

typedef struct {
    result_void (*const deserialize)(string_buffer* buf, void* target);
} Deserialize;

typedef struct {
    void* self;
    Deserialize const* vtable;
} deserializable;

inline result_void
deserialize(string_buffer* buf, deserializable* target)
{
    return target->vtable->deserialize(buf, target->self);
}

#endif

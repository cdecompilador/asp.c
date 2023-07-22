#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "util.h"
#include "result.h"
#include "string_buffer.h"

/* Serialize interface */
typedef struct {
    /* */
    result_void (*const serialize)(void* self, string_buffer* buf);
} Serialize; 

typedef struct {
    void* self;
    Serialize const* vtable;
} serializable;

result_void
serialize(serializable* self, string_buffer* buf);

#endif

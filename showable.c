#include "showable.h"

#include <stdio.h>

void 
byte_vector_show(void* _self)
{
    byte_vector_t* self = (byte_vector_t*)_self;

    printf("byte_vector [ ");
    for (int i = 0; i < self->count; i++) {
        u8 val = *(self->data + i);
        printf("%d ", val);
    }
    printf("]");
}

showable
byte_vector_showable(byte_vector_t* bv)
{
    static Show byte_vector_show_vtable = (Show) {
        .show = byte_vector_show
    };

    return (showable) {
        .self = bv,
        .vtable = &byte_vector_show_vtable
    };
}

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

void
s_hash_table_show(void* _self)
{
    string_hash_table* self = (string_hash_table*)_self;

    printf("string_hash_table {");
    for (int i = 0; i < self->table_size; i++) {
        entry* e = self->entries + i;
        if (!e->is_filled) {
            printf("* ");
        } else {
            printf("{ %d: %.*s } ", i, e->value.byte_vector.count, e->value.byte_vector.data);
        }
    }
    printf("}");
}

showable
s_hash_table_showable(string_hash_table* self)
{
    static Show s_hash_table_vtable = {
        .show = s_hash_table_show
    };

    return (showable) {
        .self = self,
        .vtable = &s_hash_table_vtable
    };
}

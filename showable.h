/* Show interface */
typedef struct {
    /* Show a human readable representation of the implementor struct */
    void (*const show)(void* self);
} Show;

/* Show interface instance */
typedef struct {
    void* self;
    Show const* vtable;
} showable;

inline void
show(showable* s)
{
    s->vtable->show(s->self);
}

/* byte_vector_t impl */
#include "vector.h"
void 
byte_vector_show(void* _self);
showable
byte_vector_showable(byte_vector_t* bv);

/* hash_table impl */
#include "hash_table.h"
void
s_hash_table_show(void* _self);
showable
s_hash_table_showable(string_hash_table* self);

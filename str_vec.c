#include "str_vec.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

str_vec_t
str_vec_create()
{
    const usize initial_capacity = 12;

    const char** data = (const char**)malloc(initial_capacity);

    if (data == NULL) {
        fprintf(stderr, "Error: Couldn't allocate\n");
        exit(1);
    }

    return (str_vec_t) {
        .data = data,
        .cap = initial_capacity,
        .count = 0
    };
}

void 
str_vec_push(str_vec_t* v, const char* buf)
{
    const char** ptr;

    /* Check if its needed to extend the allocated data capacity */
    if (v->count == v->cap) {
        v->cap *= 2;
        const char** data = realloc(v->data, v->cap * sizeof(void*));
        
        if (data == NULL) {
            fprintf(stderr, "Error: Failed to reallocate data on byte_vector_t\n");
            exit(1);
        }

        v->data = data;
    }

    /* Push data to the end */
    ptr = (const char**)v->data;
    ptr += v->count * sizeof(void*);
    v->count++;
    *ptr = buf;
}

void
str_vec_clear(str_vec_t* v)
{
    v->count = 0;
}

void
str_vec_destroy(str_vec_t* v)
{
    free(v->data);
}

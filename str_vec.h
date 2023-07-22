#ifndef STR_VECTOR_H
#define STR_VECTOR_H

#include "util.h"

/* A fake FIFO dynamic array with stack operations. It does not shrink, it just 
 * reduces it's count when `str_vec_pop` is called */
typedef struct {
    /* Count of existing strs of the vector */
    u32 count;

    /* Allocated capacity for the array stack. Always cap >= count */
    u32 cap;

    /* The data */
    const char** data;
} str_vec_t;

/* Create an `str_vec_t` on the heap and return a pointer to it */
str_vec_t
str_vec_create();

/* Push str on the vec (can trigger a realloc) */
void 
str_vec_push(str_vec_t* bv, const char* buf);

/* Clears the vector (doesn't deallocate) */
void
str_vec_clear(str_vec_t* v);

/* Frees the allocated bytes */
void
str_vec_destroy(str_vec_t* v);

#endif

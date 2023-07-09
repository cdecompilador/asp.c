#ifndef BYTE_VECTOR_H
#define BYTE_VECTOR_H

#include "util.h"

/* A fake FIFO dynamic array with stack operations. It does not shrink, it just 
 * reduces it's count when `bv_pop` is called */
typedef struct {
    /* Count of existing elements of the array stack */
    u32 count;

    /* Allocated capacity for the array stack. Always cap >= count */
    u32 cap;

    /* The data */
    u8* data;
} byte_vector_t;

/* Create an `byte_vector_t` on the heap and return a pointer to it */
byte_vector_t
bvec_create(usize size);

/* Destroy an `byte_vector_t`, removing it from the heap */
void 
bvec_destroy(byte_vector_t* bv);

/* Pop the first element from the stack */
u8 
bvec_pop(byte_vector_t* bv);

/* Push byte on the stack (can trigger a realloc) */
void 
bvec_push(byte_vector_t* bv, u8 byte);

/* Read and Writes, they don't need to be inside the interface BufferedRW.
 * The writes are done at the end of the buffer 
 */
void
bvec_write_from(byte_vector_t* bv, const u8* buffer, usize buffer_size);
void
bvec_read_to(byte_vector_t* bv, u8* buffer, usize buffer_size);

#endif

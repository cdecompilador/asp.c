#ifndef BYTE_VECTOR_H
#define BYTE_VECTOR_H

#include "util.h"

typedef struct {
    u8* buffer;
    usize buffer_size;
} byte_slice;

inline byte_slice
byte_slice_from(u8 buffer[], usize buffer_size)
{
    return (byte_slice) {
        .buffer = (u8*)buffer,
        .buffer_size = buffer_size
    };
}

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

void
bvec_reserve(byte_vector_t* self, usize extra_size);

/* Read and Writes, they don't need to be inside the interface BufferedRW.
 * The writes are done at the end of the buffer 
 */
void
bvec_write_from(byte_vector_t* bv, const u8* buffer, usize buffer_size);
void
bvec_read_to(byte_vector_t* bv, u8* buffer, usize buffer_size);

/* A fake FIFO dynamic array with stack operations. It can hold any kind of
 * element as long as it has known size */
typedef struct {
    /* Size of each allocated element */
    usize element_size;

    /* Count of existing elements of the array stack */
    u32 count;

    /* Allocated capacity for the array stack. Always cap >= count */
    u32 cap;

    /* The data */
    u8* data;
} abstract_vector;

/* Creates an abstract_vector for elements of size `element_size` */
abstract_vector
abstract_vector_create(usize element_size);

/* Frees its allocated memory */
void
abstract_vector_destroy(abstract_vector* self);

/* Push a new element, can crash */
void
abstract_vector_push(abstract_vector* self, void* elem);

/* Removes a element, can crash */
void*
abstract_vector_pop(abstract_vector* self);

/* Index the vector (with bounds checking) */
void*
abstract_vector_index(abstract_vector* self, usize idx);

#endif

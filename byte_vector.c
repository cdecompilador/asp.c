#include "byte_vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

byte_vector_t
bvec_create(usize initial_capacity)
{
    u8* data = (u8*)malloc(initial_capacity);

    if (data == NULL) {
        fprintf(stderr, "Error: Couldn't allocate\n");
        exit(1);
    }

    return (byte_vector_t) {
        .data = data,
        .cap = initial_capacity,
        .count = 0
    };
}

void 
bvec_destroy(byte_vector_t* bv)
{
    free(bv->data);
}

u8 
bvec_pop(byte_vector_t* bv) 
{
    if (bv->count == 0) {
        fprintf(stderr, "Error: attempted to pop on an empty byte_vector\n");
        exit(1);
    }

    u8* ret = bv->data;

    ret += bv->count;
    bv->count--;

    return *ret;
}

void 
bvec_push(byte_vector_t* bv, u8 byte)
{
    u8* ptr;

    /* Check if its needed to extend the allocated data capacity */
    if (bv->count == bv->cap) {
        bv->cap *= 2;
        u8* data = realloc(bv->data, bv->cap);
        
        if (data == NULL) {
            fprintf(stderr, "Error: Failed to reallocate data on byte_vector_t\n");
            exit(1);
        }

        bv->data = data;
    }

    /* Push data to the end */
    ptr = (u8*)bv->data;
    ptr += bv->count;
    bv->count++;
    *ptr = byte;
}

void
bvec_write_from(byte_vector_t* bv, const u8* buffer, usize buffer_size)
{
    /* Realloc until the data buffer is big enough */
    while (bv->cap < bv->count + buffer_size) {
        bv->cap *= 2;
        u8* data = realloc(bv->data, bv->cap);
        
        if (data == NULL) {
            fprintf(stderr, "Error: Failed to reallocate data on byte_vector_t\n");
            exit(1);
        }
        
        bv->data = data;
    }

    /* Do the memcpy */
    memcpy(bv->data + bv->count, buffer, buffer_size);
    bv->count += buffer_size;
}

void
bvec_read_to(byte_vector_t* bv, u8* buffer, usize buffer_size)
{
    /* Check if the destructive read can be done */
    if (buffer_size > bv->count) {
        fprintf(stderr, "Error: Failed read (destructive) on byte_vector_t\n");
        exit(1);
    }
    
    /* Do the memcpy */
    memcpy(buffer, bv->data + bv->count - buffer_size, buffer_size);
    bv->count -= buffer_size;
}

#include "vector.h"

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
bvec_reserve(byte_vector_t* self, usize extra_size)
{
    self->cap += extra_size;
    u8* data = realloc(self->data, self->cap);

    if (data == NULL) {
        fprintf(stderr, "Error: failed to reallocate on reserve on byte_vector_t\n");
        exit(1);
    }
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

abstract_vector
abstract_vector_create(usize element_size)
{
    const usize initial_capacity = 16;
    
    void* data = malloc(initial_capacity * element_size);

    if (data == NULL) {
        fprintf(stderr, "Couldn't Allocate\n");
        exit(1);
    }

    return (abstract_vector) {
        .data = data,
        .cap = initial_capacity,
        .count = 0,
        .element_size = element_size
    };
}

void
abstract_vector_destroy(abstract_vector* self)
{
    for (usize i = 0; i < self->count; i++) {
        void* ptr = abstract_vector_index(self, i);
        free(ptr);
    }
    free(self->data);
}

void
abstract_vector_push(abstract_vector* self, void* new_elem)
{
    void* ptr;

    /* Check if its needed to reallocate */
    if (self->count == self->cap) {
        self->cap *= 2;
        self->data = realloc(self->data, self->cap * self->element_size);

        if (self->data == NULL) {
            fprintf(stderr, "Couldn't Allocate\n");
            exit(1);
        }
    }

    /* Push data */
    ptr = self->data;
    ptr += self->count * self->element_size;
    self->count++;

    if (new_elem != NULL) memcpy(ptr, new_elem, self->element_size);
}

void*
abstract_vector_pop(abstract_vector* self)
{
    void* ptr;

    if (self->count == 0) {
        fprintf(stderr, "Error: attempted to pop on empty abstract vector");
        exit(1);
    }

    ptr = self->data;
    self->count--;
    ptr += self->count * self->element_size;

    return ptr;
}

void*
abstract_vector_index(abstract_vector* self, usize idx)
{
    void* ptr;

    if (idx >= self->count) {
        fprintf(stderr, "Error: attempted to index at invalid position, abstract vector");
        exit(1);
    }

    ptr = self->data;
    ptr += idx * self->element_size;

    return ptr;
}

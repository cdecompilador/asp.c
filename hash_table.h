#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "string_buffer.h"

typedef struct {
    /* SAFETY: Since the first member of `string_buffer` will be the pointer to
     * the string, assuming that if it equals NULL (0) which as a bool is false
     * makes this union valid */
    bool is_filled;
    string_view key;
    string_buffer value;
} entry;

/* JDK like hash table optimized for strings xor accumulation as hash function,
 * designed for strings */
typedef struct {
    entry* entries;
    usize table_size;
} string_hash_table;

inline string_hash_table
s_hash_table_create(usize size)
{
    entry* entries = (entry*)calloc(size, sizeof(entry));
    if (entries == NULL) {
        fprintf(stderr, "Error: Failed to allocate hashmap");
        exit(1);
    }
    
    return (string_hash_table) {
        .entries = entries,
        .table_size = size
    };
}

inline usize
hash_string(string_view view, usize M)
{
    usize hash = 0;

    for (int i = 0; i < view.len; i++) {
        usize chr = *(usize*)(view.ptr + i);
        
        hash ^= chr;
    }

    return hash % M;
}

inline result_void
s_hash_table_insert(
    string_hash_table* self,
    string_view key, string_buffer value
) {
    usize hash = hash_string(key, self->table_size);
    
    entry e = (entry) { .is_filled = true, .key = key, .value = value };

    bool error = true;
    for (int i = 0; i < self->table_size; i++) {
        usize idx = (hash + i) % self->table_size;
        entry* curr_entry = self->entries + idx;

        if (!curr_entry->is_filled) {
            /* Insert the string at the index */
            *curr_entry = e;

            error = false;
            break;
        }
    }

    if (error) {
        return ERR(result_void, message_error("hash_table is full"));
    }

    return OK(result_void, NULL);
}

inline bool
s_hash_table_contains(string_hash_table* self, string_view key) {
    usize idx = hash_string(key, self->table_size);

    return (self->entries + idx)->is_filled;
}

inline entry
s_hash_table_get(string_hash_table* self, string_view key) {
    usize idx = hash_string(key, self->table_size);

    return *(self->entries + idx);
}

#endif

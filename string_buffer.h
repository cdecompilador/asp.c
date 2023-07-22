#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#include <string.h>

#include "util.h"
#include "result.h"
#include "byte_vector.h"
#include "byte_slice.h"

typedef struct {
    const char* ptr;
    usize len;
} string_view;

typedef struct {
    bool success;
    union {
        string_view value;
        error_like error;
    };
} string_view_result;

inline
string_view
string_view_from(const char* str)
{
    return (string_view) {
        .ptr = str,
        .len = strlen(str)
    };
}

inline
string_view_result
string_view_slice(const string_view* sv, usize start, usize end)
{
    if (end <= start) {
        return ERR(string_view_result, message_error("slice range is invalid"));
    }

    usize len = end - start;

    return OK(
        string_view_result,
        ((string_view) {
            .ptr = sv->ptr + start,
            .len = len
        })
    );
}

typedef struct {
    byte_vector_t byte_vector;
} string_buffer;

typedef struct {
    bool success;
    union {
        string_buffer value;
        error_like error;
    };
} string_buffer_result;

string_buffer
string_buffer_empty();

string_buffer
string_buffer_create(const char* str);

void
string_buffer_push_str(string_buffer* self, const char* str);

void
string_buffer_push_char(string_buffer* self, char ch);

void
string_buffer_push(string_buffer* self, string_view view);

string_view
string_buffer_as_slice(string_buffer* self);

string_view_result
string_buffer_slice(string_buffer* self, usize start, usize end);

byte_slice
string_buffer_to_byte_slice(string_buffer* self);

void
string_buffer_destroy(string_buffer* self);

#endif

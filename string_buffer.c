#include "string_buffer.h"

#include <stdarg.h>

string_buffer
string_buffer_empty()
{
    byte_vector_t bv = bvec_create(10);
    return (string_buffer) {
        .byte_vector = bv
    };
}

string_buffer
string_buffer_create(const char* str)
{
    string_buffer sb = string_buffer_empty();

    string_buffer_push_str(&sb, str);

    return sb;
}

void
string_buffer_push_str(string_buffer* self, const char* str)
{
    usize len = strlen(str);
    bvec_write_from(&self->byte_vector, (const u8*)str, len);
}

void
string_buffer_push_char(string_buffer* self, char ch)
{
    bvec_push(&self->byte_vector, ch);
}

void
string_buffer_push(string_buffer* self, string_view view)
{
    bvec_write_from(&self->byte_vector, (const u8*)view.ptr, view.len);
}

string_view
string_buffer_as_slice(string_buffer* self)
{
    const u8* ptr = self->byte_vector.data;
    usize len = self->byte_vector.count;

    return (string_view) {
        .ptr = (const char*)ptr,
        .len = len
    };
}

string_view_result
string_buffer_slice(string_buffer* self, usize start, usize end)
{
    string_view sb = string_buffer_as_slice(self);
    return string_view_slice(&sb, start, end);
}

byte_slice
string_buffer_to_byte_slice(string_buffer* self)
{
    string_view sb = string_buffer_as_slice(self);

    return (byte_slice) {
        .buffer = (u8*)sb.ptr,
        .buffer_size = sb.len
    };
}

void
string_buffer_push_format(string_buffer* self, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    u8* buf_ptr = self->byte_vector.data + self->byte_vector.count;

    bvec_reserve(&self->byte_vector, 64);
    int len = vsnprintf((char*)buf_ptr, 64, format, args);

    if (len < 0) {
        fprintf(stderr, "Error");
        exit(1);
    }

    self->byte_vector.count += len;

    va_end(args);
}

void
string_buffer_destroy(string_buffer* self)
{
    bvec_destroy(&self->byte_vector);
}


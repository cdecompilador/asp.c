#include "http_body.h"

#include "http_body_raw_text.h"

http_body_like
raw_text_from(const char* c_str)
{
    /* Needs to be alloc :( */
    raw_text* raw_text_instance = (raw_text*)malloc(sizeof(raw_text));
    raw_text_instance->str = string_buffer_create(c_str);

    return (http_body_like) {
        .self = raw_text_instance,
        .vtable = get_raw_text_vtable()
    };
}

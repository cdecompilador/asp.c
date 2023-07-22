#include "http_body_raw_text.h"
#include "serialize_string_buffer.h"

serializable
raw_text_to_serializable(void* _self)
{
    raw_text* self = (raw_text*)_self;

    return string_buffer_serializable(&self->str);
}

string_view
raw_text_content_type()
{
    return string_view_from("text/plain");
}

void
raw_text_free(void* _self)
{
    raw_text* self = (raw_text*)_self;

    string_buffer_destroy(&self->str);
}

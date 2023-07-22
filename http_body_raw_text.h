#ifndef SERIALIZE_RAW_TEXT_H
#define SERIALIZE_RAW_TEXT_H

#include "serialize.h"
#include "http_body.h"

serializable
raw_text_to_serializable(void* _self);

string_view
raw_text_content_type();

void
raw_text_free(void* _self);

inline HttpBody*
get_raw_text_vtable()
{
    static HttpBody raw_text_vtable = (HttpBody) {
        .to_serializable = raw_text_to_serializable,
        .content_type = raw_text_content_type,
        .free = raw_text_free
    };

    return &raw_text_vtable;
}

#endif

#ifndef HTTP_BODY
#define HTTP_BODY

#include "util.h"
#include "string_buffer.h"
#include "serialize.h"

typedef struct {
    serializable (*const to_serializable)(void* self);
    string_view (*const content_type)();
    void (*const free)(void* self);
} HttpBody;

typedef struct {
    void* self;
    HttpBody* vtable;
} http_body_like;

inline serializable
to_serializable(http_body_like* self)
{
    return self->vtable->to_serializable(self->self);
}

inline string_view
content_type(http_body_like* self)
{
    return self->vtable->content_type();
}

inline void
http_body_like_free(http_body_like* self)
{
    self->vtable->free(self->self);
    free(self->self);
}

typedef struct {
    string_buffer str;
} raw_text;

http_body_like
raw_text_from(const char* c_str);

#endif

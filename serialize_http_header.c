#include "serialize_http_header.h"

result_void
http_request_header_serialize(void* _self, string_buffer* buf)
{
    http_request_header* self = (http_request_header*)_self;

    /* Serialize method */
    switch (self->method) {
    case GET:
        string_buffer_push_str(buf, "GET ");
        break;
    case POST:
        string_buffer_push_str(buf, "POST ");
        break;
    case HEAD:
        string_buffer_push_str(buf, "HEAD ");
        break;
    }
    
    /* Serialize URI */
    string_buffer_push(buf, string_buffer_as_slice(&self->uri));
    
    /* Serialize HTTP version */
    string_buffer_push_str(buf, " HTTP/1.0\r\n"); // <- tarmo pone \n\r

    /* Serialize HTTP headers */
    for (int i = 0; i < self->headers.table_size; i++) {
        entry* e = self->headers.entries + i;

        if (e->is_filled) {
            string_buffer_push(buf, e->key);
            string_buffer_push_str(buf, ": ");
            string_buffer_push(buf, string_buffer_as_slice(&e->value));
            string_buffer_push_str(buf, "\r\n");
        }
    }

    return OK(result_void, NULL);
}

serializable
http_request_header_serializable(http_request_header* self)
{
    static Serialize http_request_header_serialize_vtable = (Serialize) {
        .serialize = http_request_header_serialize
    };

    return (serializable) {
        .self = self,
        .vtable = &http_request_header_serialize_vtable
    };
}

result_void
http_response_header_serialize(void* _self, string_buffer* buf)
{
    http_response_header* self = (http_response_header*)_self;

    /* Serialize status code */
    string_buffer_push_format(
            buf,
            "HTTP/1.0 %d %s\r\n", 
            self->status_code,
            status_code_message(self->status_code));

    /* Serialize HTTP headers */
    for (int i = 0; i < self->headers.table_size; i++) {
        entry* e = self->headers.entries + i;

        if (e->is_filled) {
            string_buffer_push(buf, e->key);
            string_buffer_push_str(buf, ": ");
            string_buffer_push(buf, string_buffer_as_slice(&e->value));
            string_buffer_push_str(buf, "\r\n");
        }
    }

    return OK(result_void, NULL);
}

serializable
http_response_header_serializable(http_response_header* self)
{
    static Serialize http_response_header_serialize_vtable = (Serialize) {
        .serialize = http_response_header_serialize
    };

    return (serializable) {
        .self = self,
        .vtable = &http_response_header_serialize_vtable
    };
}



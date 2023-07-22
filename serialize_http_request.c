#include "serialize_http_request.h"

#include "serialize_http_header.h"
#include "http_request.h"
#include "http_body.h"

result_void
#define CHECK(_result) RES_CHECK(result_void, _result)
http_request_serialize(void* _self, string_buffer* buf)
{
    http_request* self = (http_request*)_self;

    /* Serialize header */
    serializable ser_header = http_header_serializable(&self->header);
    CHECK(serialize(&ser_header, buf));
    string_buffer_push_str(buf, "Content-Type: ");
    string_buffer_push(buf, content_type(&self->body));
    
    /* HTTP header and body separator */
    string_buffer_push_str(buf, "\r\n\r\n");

    /* Serialize body */
    serializable ser_body = to_serializable(&self->body);
    CHECK(serialize(&ser_body, buf));

    return OK(result_void, NULL);
}
#undef CHECK

serializable
http_request_serializable(void* self)
{
    static Serialize http_request_serialize_vtable = (Serialize) {
        .serialize = http_request_serialize
    };

    return (serializable) {
        .self = self,
        .vtable = &http_request_serialize_vtable
    };
}

#include "serialize_http_response.h"

#include "http_response.h"

result_void
#define CHECK(_result) RES_CHECK(result_void, _result)
http_response_serialize(void* _self, string_buffer* buf)
{
    http_response* self = (http_response*)_self;

    /* Serialize the header */
}
#undef CHECK

serializable
http_response_serializable(void* _self);


#ifndef SERIALIZE_HTTP_REQUEST
#define SERIALIZE_HTTP_REQUEST

#include "result.h"
#include "serialize.h"

result_void
http_request_serialize(void* _self, string_buffer* buf);

serializable
http_request_serializable(void* _self);

#endif

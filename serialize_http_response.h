#ifndef SERIALIZE_HTTP_RESPONSE_H
#define SERIALIZE_HTTP_RESPONSE_H

#include "result.h"
#include "serialize.h"
#include "string_buffer.h"

result_void
http_response_serialize(void* _self, string_buffer* buf);

serializable
http_response_serializable(void* _self);

#endif

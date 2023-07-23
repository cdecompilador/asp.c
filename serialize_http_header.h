#ifndef SERIALIZE_HTTP_HEADER_H
#define SERIALIZE_HTTP_HEADER_H

#include "result.h"
#include "serialize.h"
#include "string_buffer.h"
#include "http_request.h"
#include "http_response.h"

result_void
http_request_header_serialize(void* _self, string_buffer* buf);

serializable
http_request_header_serializable(http_request_header* self);

/* TODO
result_void
http_request_header_deserialize(string_buffer* buf, void* _self);

deserializable
http_request_header_deserializable(string_buffer* buf);
*/

result_void
http_response_header_serialize(void* _self, string_buffer* buf);

serializable
http_response_header_serializable(http_response_header* self);

#endif

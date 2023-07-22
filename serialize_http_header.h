#ifndef SERIALIZE_HTTP_HEADER_H
#define SERIALIZE_HTTP_HEADER_H

#include "result.h"
#include "serialize.h"
#include "string_buffer.h"
#include "http_request.h"

result_void
http_header_serialize(void* self, string_buffer* buf);

serializable
http_header_serializable(http_header* self);

#endif

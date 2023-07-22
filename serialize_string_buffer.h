#ifndef SERIALIZE_STRING_BUFFER_H
#define SERIALIZE_STRING_BUFFER_H

#include "string_buffer.h"
#include "serialize.h"

result_void
string_buffer_serialize(void* self, string_buffer* buf);

serializable
string_buffer_serializable(string_buffer* self);

#endif

#include "serialize_string_buffer.h"

result_void
string_buffer_serialize(void* _self, string_buffer* buf)
{
    string_buffer* self = (string_buffer*)_self;
    string_view slice = string_buffer_as_slice(self);
    string_buffer_push(buf, slice);

    return OK(result_void, NULL);
}

serializable
string_buffer_serializable(string_buffer* self)
{
    static Serialize string_buffer_serialize_vtable = (Serialize) {
        .serialize = string_buffer_serialize
    };

    return (serializable) {
        .self = self,
        .vtable = &string_buffer_serialize_vtable
    };
}

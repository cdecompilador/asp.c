#include "serialize.h"
#include "string_buffer.h"

result_void
serialize(serializable* self, string_buffer* buf)
{
    RES_CHECK(result_void, (self->vtable->serialize(self->self, buf)));

    return OK(result_void, NULL);
}

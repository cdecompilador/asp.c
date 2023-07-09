#include "error.h"
#include "result.h"

void
message_error_describe(const void* _self)
{   
    message_error_t* self = (message_error_t*)_self;

    CONTEXT("%s", self->message);
}

int
message_error_variant(const void* _self)
{
    return 0;
}

error_like
message_error(const char* message)
{
    static Error message_error_vtable = (Error) {
        .describe = message_error_describe,
        .variant = message_error_variant
    };

    static message_error_t message_error_instance = {0};
    message_error_instance.message = message;

    return (error_like) {
        .self = &message_error_instance,
        .vtable = &message_error_vtable
    };
}

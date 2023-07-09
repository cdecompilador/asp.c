#include "result.h"

str_vec_t
error_backtrace = {0};

void
backtrace_init()
{
    error_backtrace = str_vec_create();
}

void
print_backtrace()
{
    if (error_backtrace.count == 0)
        printf("No backtrace\n");
    else 
        printf("Backtrace:\n");

    for (int i = 0; i < error_backtrace.count; i++) {
        printf("\t%d : %s\n", i, *(error_backtrace.data + i * sizeof(void*)));
    }
}

void
clear_backtrace()
{
    str_vec_clear(&error_backtrace);
}

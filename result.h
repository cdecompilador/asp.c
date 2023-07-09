#ifndef RESULT_H
#define RESULT_H

/* NOTE: They need to be here so the macros work properly */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "str_vec.h"
#include "error.h"

extern str_vec_t
error_backtrace;

void
backtrace_init();

void
print_backtrace();

void clear_backtrace();

#define MAX_ERROR_DESCRIBE_SIZE 128

#define OK(T, _value) (T) { .success = true, .value = (_value) }
#define ERR(T, _error) (T) { .success = false, .error = (_error) }

#define RES_CHECK(T, _result) ({\
        typeof(_result) res = (_result);\
        if (!res.success) {\
            return (T) { .success = false, .error = res.error };\
        } else {\
            clear_backtrace();\
        }\
        res.value; })

/* Takes a expression of type T (which implements Error interface), adds it to
 * the backtrace and exchanges it for a new error, useful for giving context
 * in situations where you don't want to handle errors really
 *
 * The new error show be passed the creation expression, not a saved variable,
 * since all errors from the same kind share vtable that could lead to invalid
 * results 
 *
 * Ex:
 *  WRAP(func(), message_error("bad")); <-- OK
 *  
 *  message_error_t e = message_error("bad");
 *  WRAP(func(), e);                            <-- NOT OK
 *
 *  #define E message_error("bad")
 *  WRAP(func(), E);                <-- OK but this may lead to issued later
 *  */
#define RES_WRAP(T, _result, _new_err) ({\
        typeof(_result) res = (_result);\
        if (!res.success) {\
            error_describe(res.error);\
            return (T) { .success = false, .error = _new_err };\
        } else {\
            clear_backtrace();\
        }\
        res.value; })

#define UNWRAP(_result) ({\
        typeof(_result) res = (_result);\
        if (!res.success) {\
            error_describe(res.error);\
            printf("Unhandled unwrap on %s:%d\n", __FILE__, __LINE__);\
            print_backtrace();\
            exit(1);\
        } else {\
            clear_backtrace();\
        }\
        res.value; })

typedef struct {
    bool success;
    union {
        error_like error;
        void* value;
    };
} result_void;

typedef struct {
    bool success;
    union {
        error_like error;
        usize value;
    };
} result_usize;
        
#endif

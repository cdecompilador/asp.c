#ifndef PARSER_COMBINATORS_H
#define PARSER_COMBINATORS_H

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "result.h"
#include "string_buffer.h"

typedef struct {
    bool success;
    union {
        void* value;
        error_like error;
    };
} parse_result;

typedef struct {
    string_view input_str;
    parse_result result;
} parse_state;

typedef struct {
    parse_state (*parse)(void* _self, parse_state input);
} Parser;

typedef struct {
    void* self;
    Parser vtable;
} combinator;

inline parse_state
_parse(combinator self, parse_state input)
{
    return self.vtable.parse(self.self, input);
}

inline parse_result
parse(combinator self, string_view input)
{   
    parse_state input_state = (parse_state) {
        .input_str = input,
        .result = OK(parse_result, NULL)
    };

    parse_state output_state = self.vtable.parse(self.self, input_state);

    /* TODO: Recursive free */

    return output_state.result;
}

typedef struct {
    string_view to_match;
} match_combinator;

parse_state
match_combinator_parse(void* _self, parse_state input)
{
    match_combinator* self = (match_combinator*)_self;

    string_view input_str = input.input_str;

    if (string_view_starts_with(input_str, self->to_match)) {
        string_view result;
        string_view remainder;

        UNWRAP((string_view_partition_at(input_str, self->to_match.len, &result, &remainder)));

        return (parse_state) {
            .input_str = remainder,
            .result = OK(parse_result, ((void*)&result))
        };
    } else {
        return (parse_state) {
            .input_str = input_str,
            .result = ERR(parse_result, message_error("Failed on match combinator"))
        };
    }
}

inline combinator
match(const char* to_match)
{
    match_combinator* instance = (match_combinator*)malloc(sizeof(match_combinator));
    if (instance == NULL) {
        fprintf(stderr, "Allocation failed");
        exit(1);
    }

    instance->to_match = string_view_from(to_match);

    Parser match_parser_vtable = (Parser) {
        .parse = match_combinator_parse,
    };

    return (combinator) {
        .self = (void*)instance,
        .vtable = match_parser_vtable
    };
}

typedef struct {
    combinator c1;
    combinator c2;
} either_combinator;

inline parse_state 
either_combinator_parse(void* _self, parse_state input)
{
    either_combinator* self = (either_combinator*)_self;

    parse_state c1_state = _parse(self->c1, input);
    if (c1_state.result.success)
        return c1_state;

    parse_state c2_state = _parse(self->c2, input);
    if (c2_state.result.success)
        return c2_state;

    return (parse_state) {
        .input_str = input.input_str,
        .result = ERR(parse_result, message_error("Failed on either combinator"))
    };
}

inline combinator
either(combinator c1, combinator c2)
{
    either_combinator* instance = (either_combinator*)malloc(sizeof(either_combinator));
    if (instance == NULL) {
        fprintf(stderr, "Allocation failed");
        exit(1);
    }

    instance->c1 = c1;
    instance->c2 = c2;

    Parser either_combinator_vtable = (Parser) {
        .parse = either_combinator_parse,
    };

    return (combinator) {
        .self = (void*)instance,
        .vtable = either_combinator_vtable
    };
}

/*
void foo()
{
    combinator m1 = match("GET");
    combinator m2 = match("POST");

    combinator m3 = either(m1, m2);
}
*/

#endif

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include "util.h"
#include "string_buffer.h"
#include "hash_table.h"
#include "http_body.h"

enum http_method {
    GET,
    POST,
    HEAD
};

typedef struct {
    enum http_method method;
    string_buffer uri;
    string_hash_table headers;
} http_header;

typedef struct {
    http_header header;
    http_body_like body;
} http_request;

#endif

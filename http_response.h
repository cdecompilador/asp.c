#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "util.h"
#include "hash_table.h"
#include "http_body.h"

enum http_status_code {
    /* Successful */
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,

    /* Redirections */
    MULTIPLE_CHOICES = 300,
    MOVED_TEMPORARILY = 301,
    MOVED_PERMANENTLY = 302,
    NOT_MODIFIED = 304,

    /* Client error */
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,

    /* Server error */
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
};

inline const char*
status_code_message(enum http_status_code code)
{
    switch (code) {
    case 200: return "OK";
    case 201: return "Created";
    case 202: return "Accepted";
    case 204: return "No Content";
    case 300: return "Multiple Choices";
    case 301: return "Moved Temporarily";
    case 302: return "Moved Permanently";
    case 304: return "Not Modified";
    case 400: return "Bad Request";
    case 401: return "Unauthorized";
    case 403: return "Forbidden";
    case 404: return "Not Found";
    case 500: return "Internal Server Error";
    case 501: return "Not Implemented";
    case 502: return "Bad Gateway";
    case 503: return "Service Unavaible";
    }
}

typedef struct {
    enum http_status_code status_code;
    string_hash_table headers;
} http_response_header;

typedef struct {
    http_response_header header;
    http_body_like body;
} http_response;

#endif

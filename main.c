#include <stdio.h>    

#include "result.h"
#include "util.h"

#include "ip.h"
#include "string_buffer.h"
#include "byte_slice.h"
#include "tcp.h"
#include "hash_table.h"
#include "showable.h"
#include "http_request.h"
#include "serialize.h"
#include "serialize_http_request.h"
#include "http_response.h"
#include "parser_combinators.h"

int
main(int argc, char** argv)
{
    backtrace_init();

    /*
    http_request_header header;
    header.method = POST;
    header.uri = string_buffer_create("/usr/data");

    string_hash_table table = s_hash_table_create(3);
    string_buffer k2 = string_buffer_create("Key2");
    string_buffer v2 = string_buffer_create("Value2");
    string_buffer k3 = string_buffer_create("Key3");
    string_buffer v3 = string_buffer_create("AAA");
    string_buffer k4 = string_buffer_create("Key4");
    string_buffer v4 = string_buffer_create("BBB");
    s_hash_table_insert(&table, string_buffer_as_slice(&k2), v2);
    s_hash_table_insert(&table, string_buffer_as_slice(&k3), v3);
    s_hash_table_insert(&table, string_buffer_as_slice(&k4), v4);
    header.headers = table;

    http_request request = (http_request) {
        .header = header,
        .body = raw_text_from("hello world!")
    };

    string_buffer buf = string_buffer_empty();
    serializable s = http_request_serializable(&request);
    UNWRAP(serialize(&s, &buf));
    */ 

    /*
    string_buffer buf = string_buffer_create("Hello");
    enum http_status_code status_code = OK;
    string_buffer_push_format(
            &buf,
            "HTTP/1.0 %d %s\r\n",   
            status_code, 
            status_code_message(status_code));
    printf("%.*s\n", buf.byte_vector.count, buf.byte_vector.data);
    */

    string_buffer buf = string_buffer_create("GET ");
    string_view buf_view = string_buffer_as_slice(&buf);

    combinator space_parser = match(" ");
    combinator post_parser = match("POST");
    combinator get_parser  = match("GET");
    combinator create_parser = match("CREATE");
    combinator method_parser = either(create_parser, either(get_parser, post_parser));
    combinator final_parser = left(method_parser, space_parser);
    parse_result result = parse(final_parser, buf_view);

    if (result.success && result.value == NULL) {
        puts("Parse success");
    } else {
        puts("Parse failed");
    }

    /* 
    tcp_stream stream = UNWRAP(
        tcp_stream_connect(
            ipv4_from(
                (u8[4]) { 127, 0, 0, 1 }, 
                3000
            )
        )
    );

    byte_slice slice = byte_slice_from((u8[]){ 1, 2, 3, 4 }, 4);
    UNWRAP(tcp_stream_write(&stream, &slice));
    */

    return 0;
}

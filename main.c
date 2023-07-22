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
#include "serialize_http_header.h"
#include "http_body_raw_text.h"

int
main(int argc, char** argv)
{
    backtrace_init();
    
    /*
    string_buffer k1 = string_buffer_create("Content-Type");
    string_buffer v1 = string_buffer_create("html/text");
    string_buffer k2 = string_buffer_create("Key2");
    string_buffer v2 = string_buffer_create("Value2");
    string_buffer k3 = string_buffer_create("Key3");
    string_buffer v3 = string_buffer_create("AAA");
    string_buffer k4 = string_buffer_create("Key4");
    string_buffer v4 = string_buffer_create("BBB");

    string_hash_table table = s_hash_table_create(3);

    s_hash_table_insert(&table, string_buffer_as_slice(&k1), v1);
    s_hash_table_insert(&table, string_buffer_as_slice(&k2), v2);
    s_hash_table_insert(&table, string_buffer_as_slice(&k3), v3);
    s_hash_table_insert(&table, string_buffer_as_slice(&k4), v4);

    if (s_hash_table_contains(&table, string_buffer_as_slice(&k1))) {
        puts("YAY");
    }
    if (s_hash_table_contains(&table, string_buffer_as_slice(&k2))) {
        puts("YAY");
    }

    showable s = s_hash_table_showable(&table);
    show(&s);
    */

    http_header header;
    header.method = POST;
    header.uri = string_buffer_create("/usr/data");

    string_hash_table table = s_hash_table_create(3);
    string_buffer k1 = string_buffer_create("Content-Type");
    string_buffer v1 = string_buffer_create("html/text");
    string_buffer k2 = string_buffer_create("Key2");
    string_buffer v2 = string_buffer_create("Value2");
    string_buffer k3 = string_buffer_create("Key3");
    string_buffer v3 = string_buffer_create("AAA");
    string_buffer k4 = string_buffer_create("Key4");
    string_buffer v4 = string_buffer_create("BBB");
    s_hash_table_insert(&table, string_buffer_as_slice(&k1), v1);
    s_hash_table_insert(&table, string_buffer_as_slice(&k2), v2);
    s_hash_table_insert(&table, string_buffer_as_slice(&k3), v3);
    s_hash_table_insert(&table, string_buffer_as_slice(&k4), v4);
    header.headers = table;

    serializable s = http_header_serializable(&header);
    string_buffer buf = string_buffer_empty();
    UNWRAP(serialize(&s, &buf));
    printf("%.*s\n", buf.byte_vector.count, buf.byte_vector.data);

    http_body_like body = raw_text_from("hello world!");
    serializable ser_body = to_serializable(&body);
    string_view cont_type = content_type(&body);
    printf("Content-Type: %.*s\n", cont_type.len, cont_type.ptr);
    UNWRAP(serialize(&ser_body, &buf));
    printf("%.*s\n", buf.byte_vector.count, buf.byte_vector.data);

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

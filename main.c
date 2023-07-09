#include <stdio.h>

#include "result.h"
#include "util.h"

#include "ip.h"
#include "byte_slice.h"
#include "tcp.h"

int
main(int argc, char** argv)
{
    backtrace_init();

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

    return 0;
}

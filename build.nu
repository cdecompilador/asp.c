clang -std=gnu2x -Wall -c main.c
clang -std=gnu2x -Wall -c byte_vector.c
clang -std=gnu2x -Wall -c showable.c
clang -std=gnu2x -Wall -c str_vec.c
clang -std=gnu2x -Wall -c result.c
clang -std=gnu2x -Wall -c error.c
clang -std=gnu2x -Wall -c net_error.c
clang -std=gnu2x -Wall -c socket.c
clang -std=gnu2x -Wall -c tcp.c
clang -std=gnu2x -Wall -c string_buffer.c
clang -std=gnu2x -Wall -c serialize.c
clang -std=gnu2x -Wall -c http_body.c
clang -std=gnu2x -Wall -c serialize_string_buffer.c
clang -std=gnu2x -Wall -c serialize_http_header.c
clang -std=gnu2x -Wall -c http_body_raw_text.c
clang -std=gnu2x -Wall -c serialize_http_request.c

clang main.o byte_vector.o showable.o str_vec.o result.o socket.o error.o net_error.o tcp.o string_buffer.o serialize.c http_body.o serialize_string_buffer.o serialize_http_header.o http_body_raw_text.o serialize_http_request.o -o asp.c.exe

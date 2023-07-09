clang -std=gnu2x -Wall -c main.c
clang -std=gnu2x -Wall -c byte_vector.c
clang -std=gnu2x -Wall -c showable.c
clang -std=gnu2x -Wall -c str_vec.c
clang -std=gnu2x -Wall -c result.c
clang -std=gnu2x -Wall -c error.c
clang -std=gnu2x -Wall -c net_error.c
clang -std=gnu2x -Wall -c socket.c
clang -std=gnu2x -Wall -c tcp.c

clang main.o byte_vector.o showable.o str_vec.o result.o socket.o error.o net_error.o tcp.o -o asp.c.exe

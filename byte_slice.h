#ifndef BYTE_SLICE_H
#define BYTE_SLICE_H

#include "util.h"

typedef struct {
    u8* buffer;
    usize buffer_size;
} byte_slice;

inline byte_slice
byte_slice_from(u8 buffer[], usize buffer_size)
{
    return (byte_slice) {
        .buffer = (u8*)buffer,
        .buffer_size = buffer_size
    };
}

#endif

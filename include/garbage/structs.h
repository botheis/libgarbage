//
// Created by noel on 13/11/2025.
//

#ifndef GARBAGE_STRUCTS_H
#define GARBAGE_STRUCTS_H

#include "defs.h"

#ifdef __cplusplus
    extern "C" {
#endif

typedef void (*cleaner)(void*);

typedef struct Garbage {
    void** values;
    cleaner* callbacks;
    size_t size;
    size_t capacity;
} Garbage;

#ifdef __cplusplus
    }
#endif

#endif //GARBAGE_STRUCTS_H

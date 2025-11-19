//
// Created by noel on 13/11/2025.
//

#ifndef GARBAGE_DEFS_H
#define GARBAGE_DEFS_H

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
    extern "C" {
#endif

// Put a limitation to the garbage size
// If the GARBAGE_MAX_ALLOWED_SIZE is 0, there is no limitation
#ifndef GARBAGE_MAX_ALLOWED_SIZE
    #define GARBAGE_MAX_ALLOWED_SIZE 0
#endif

// Define the allocation steps to allocate on garbage resize
#ifndef GARBAGE_RESIZE_STEP
    #define GARBAGE_RESIZE_STEP 10
#endif

#ifdef __cplusplus
    }
#endif

#endif //GARBAGE_DEFS_H

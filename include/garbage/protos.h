//
// Created by noel on 13/11/2025.
//

#ifndef GARBAGE_PROTOS_H
#define GARBAGE_PROTOS_H

#include "structs.h"
// All these functions are manipulating a unique static Garbage* declared in the .c file

#ifdef __cplusplus
    extern "C" {
#endif

/**
 * Initialize the garbage collector
 */
void GarbageInit(void);

/**
 * Free the garbage collector and all its stored values
 */
void GarbageFree(void);

/**
 * Get the garbage object for manual manipulation.
 *
 * @return Garbage* the instance of the garbage
 */
Garbage* GarbageGet(void);

/**
 * Tells if the garbage is inited or not.
 * @return true if the garbage is inited
 * @return false if the garbage isn't inited
 */
bool GarbageInited(void);

/**
 * Push a data into the garbage collector
 *
 * @param data The data to free throuth the garbage
 * @param callback Eventually a cleanup function for specific free
 * @return true if the data has been pushed
 * @return false if the data hasn't been pushed
 */
bool GarbagePush(void* data, cleaner callback);

/**
 * Free the specified data, using the garbage collector.
 *
 * @param data The data to free.
 * @return true If the data has been freed.
 * @return false For any other cases.
 */
bool GarbagePop(const void* data);

/**
 * Remove the data from the garbage collector without freeing it.
 *
 * @param data The data to free.
 * @return If the data has been removed.
 * @return false For any other cases.
 */
bool GarbageRemove(const void* data);

/**
 * Replace an old data by a new one. Usefull for realloc cases. The old data is removed from the garbage without freeing it.
 *
 * @param old The data to replace.
 * @param new The new data to push.
 * @param callback Eventually a callback to cleanup the new data (replace the old callback).
 * @return true If the old data has been replaced.
 * @return false For any other cases.
 */
bool GarbageReplace(const void* old, void* _new, cleaner callback);

/**
 * Calculate the garbage capacity. Used internally to check if the garbage needs to be resized.
 * @return The garbage's capacity
 */
float GarbageCapacity(void);

/**
 * Resize the garbage when needed. Used internally during a push execution.
 *
 * @param capacity the new capacity of the garbage. If the capacity is lower than the garbage capacity. It set by default to the garbage capacity + 10.
 * @return true If the  garbage has been resized.
 * @return false For any other cases
 */
bool GarbageResize(size_t capacity);


#ifdef __cplusplus
    }
#endif

#endif //GARBAGE_PROTOS_H

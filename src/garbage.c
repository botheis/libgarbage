//
// Created by noel on 14/11/2025.
//
#include "../include/garbage/garbage.h"

/**
 * Define one and unique garbage collector
 */
static Garbage* garbage = NULL;


Garbage* GarbageGet(void) {
    return garbage;
}


void GarbageInit(void) {
    // Init once the garbage
    if (GarbageInited() == true) {
        return;
    }

    garbage = (Garbage*)calloc(1, sizeof(Garbage));
    if (garbage == NULL) {
        return;
    }

    garbage->values = (void**)calloc(1, sizeof(void*));
    if (garbage->values == NULL) {
        // Do not keep partially initialized datas
        free(garbage);
        garbage = NULL;
        return;
    }


    garbage->callbacks = (cleaner*)calloc(1, sizeof(cleaner));
    if (garbage->callbacks == NULL) {
        // Do not keep partially initialized datas
        free(garbage->values);
        garbage->values = NULL;
        free(garbage);
        garbage = NULL;
        return;
    }

    // Free slots = capacity - size
    garbage->size = 0;
    garbage->capacity = 1;
}


void GarbageFree(void) {
    if (GarbageInited() == false) {
        return;
    }

    for (size_t i = 0; i < garbage->capacity; i++) {
        // Free values on non-empty slots
        if (garbage->values[i] != NULL) {

            // Case 1 : a callback is given to the garbage: use it
            if (garbage->callbacks[i] != NULL) {
                garbage->callbacks[i](garbage->values[i]);
            }
            // Case 2 : no callback given: use free
            else {
                free(garbage->values[i]);
            }
            garbage->values[i] = NULL;
            garbage->callbacks[i] = NULL;
        }
    }

    // Free containers
    free(garbage->values);
    garbage->values = NULL;

    free(garbage->callbacks);
    garbage->callbacks = NULL;

    garbage->capacity = 0;
    garbage->size = 0;

    // Free garbage
    free(garbage);
    garbage = NULL;
}


bool GarbageInited(void) {
    return garbage != NULL && garbage->values != NULL && garbage->capacity > 0;
}


bool GarbagePush(void* data, cleaner callback) {
    if (GarbageInited() == false || data == NULL) {
        return false;
    }

    // Do not wait until the garbage is full to proceed to a resize
    if (GarbageCapacity() > 0.9) {
        const bool result = GarbageResize(garbage->capacity+10);

        // Resize failed, we can't continue
        if (result == false) {
            return false;
        }
    }

    // TODO : change index = 0 by something a little better for performances
    // Get first empty
    size_t index = 0;
    bool found = false;
    for (size_t i = 0; i < garbage->capacity; i++) {
        if (garbage->values[i] == NULL) {
            index = i;
            found = true;
            break;
        }
    }

    // No empty slot found : can't continue
    if (found == false) {
        return false;
    }

    // Push the data and its callback into the garbage
    garbage->values[index] = data;
    garbage->callbacks[index] = callback;
    garbage->size++;

    return true;
}


bool GarbagePop(const void* data) {
    if (GarbageInited() == false || data == NULL) {
        return false;
    }

    // Find the slot with the data
    for (size_t i = 0; i < garbage->capacity; i++) {
        if (garbage->values[i] == data) {
            // Freed by callback
            if (garbage->callbacks[i] == NULL) {
                free(garbage->values[i]);
            }
            // Freed by free function
            else {
                garbage->callbacks[i](garbage->values[i]);
            }
            garbage->values[i] = NULL;
            garbage->size--;

            return true;
        }
    }
    // The data is not in the garbage
    return false;
}


bool GarbageRemove(const void* data) {
    if (GarbageInited() == false || data == NULL) {
        return false;
    }
    // Try to find the data
    for (size_t i = 0; i < garbage->capacity; i++) {
        if (garbage->values[i] == data) {
            garbage->values[i] = NULL;
            garbage->callbacks[i] = NULL;
            garbage->size--;
            return true;
        }
    }
    // Data not found
    return false;
}


bool GarbageReplace(const void* old, void* _new, cleaner callback) {
    if (GarbageInited() == false || old == NULL || _new == NULL) {
        return false;
    }

    for (size_t i = 0; i < garbage->capacity; i++) {
        if (garbage->values[i] == old) {
            garbage->values[i] = _new;
            garbage->callbacks[i] = callback;
            return true;
        }
    }
    return false;
}

float GarbageCapacity(void) {
    if(GarbageInited() == false){
        return 0.0;
    }
    return 1.0*garbage->size / garbage->capacity*1.0;
}

bool GarbageResize(size_t capacity) {
    if (GarbageInited() == false) {
        return false;
    }

    // Limit reached
    if (GARBAGE_MAX_ALLOWED_SIZE != 0 && garbage->capacity == GARBAGE_MAX_ALLOWED_SIZE) {
        return false;
    }

    // the new capacity must be greater than the garbage capacity
    if (capacity <= garbage->capacity) {
        capacity = garbage->capacity + GARBAGE_RESIZE_STEP;
    }

    // Check if this limit fits with the GARBAGE_MAX_ALLOWED_SIZE
    if (GARBAGE_MAX_ALLOWED_SIZE != 0 && GARBAGE_MAX_ALLOWED_SIZE < capacity) {
        capacity = GARBAGE_MAX_ALLOWED_SIZE;
    }

    void** newValues = realloc(garbage->values, capacity*sizeof(void*));
    cleaner* newCallbacks = realloc(garbage->callbacks, capacity*sizeof(cleaner));

    // Don't lose the new pointers
    if (newValues != NULL) {
        // set to NULL the pointers
        for (size_t i = garbage->capacity; i < capacity; i++) {
            newValues[i] = NULL;
        }
        garbage->values = newValues;
    }

    if (newCallbacks != NULL) {
        // Set to NULL the pointers
        for (size_t i = garbage->capacity; i < capacity; i++) {
            newCallbacks[i] = NULL;
        }
        garbage->callbacks = newCallbacks;
    }

    // Success, don't forget to change the garbage capacity
    if (newValues != NULL && newCallbacks != NULL) {
        garbage->capacity = capacity;
        return true;
    }

    // On this case, we don't change the garbage capacity, to avoid to call out of bounds values
    return false;
}

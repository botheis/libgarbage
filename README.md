Lib garbage
===

- Author : Noël Kneib [botheis@github.com](https://github.com/botheis) 
- Version : 1.0
- Creation Date: 2025-11-15
- License: GPL-v3

# What is libgarbage?

Libgarbage is a small library that gives the user the possibility to allocate memory, and through the libgarbage, dynamically free it.

# How to install ?

After you downloaded and extracted this archive, you have to compile it:

```bash

cd /folder/to/libgarbage
make
sudo make install
sudo ldconfig

```

# How use it ?

## Linkage

The libgarbage is provided with a pkg-config command:

```bash
pkg-config garbage --cflags --libs

# Result of pkg-config
# -I/usr/local/include -L/usr/local/lib -lgarbage 
```

# Include

Basically the shape of the header you have to use depends on how you specify your cflags.   
By default, and considering you use the pkg-config infos, you can use the following include:
```c++
#include <garbage/garbage.h>
// There are other header files, don't include them directly !
```

# Where to find the documentation ?

You can find some examples into the examples folder. Further more on the header files you will be able to get the whole possibilities that this lib offers.

We can provide the list of prototypes here to help you a little:

```c++
// To launch before using the lib
void GarbageInit();

// To launch before leaving
void GarbageFree();

// For specific usage. 
// You should not need to manipulate directly the garbage
Garbage* GarbageGet();

// Check if the garbage collector has been correctly inited
bool GarbageInited();

// Push the data into the garbage collector. 
// A callback can be specified for specific frees.
bool GarbagePush(void* data, cleaner callback);

// To define your own cleaners, you have to respect this definition :
typedef void (*cleaner)(void*);

// To clean individually a data.
bool GarbagePop(void* data);

// Remove the data from the garbage without freeing it
bool GarbageRemove(void* data);

// Replace the old pointer by the new one. 
// Usefull when we use realloc on a pointer 
// and it results a new pointer to replace the previous one.
bool GarbageReplace(void* old, void* _new, cleaner callback);

// Gives the ratio of occupation of the garbage with the current capacity.
float GarbageCapacity();

// Resize the garbage. Increase the garbage up to the specified capacity.
bool GarbageResize(size_t capacity);
```

# Is this lib usable in C++ ?

Theorically yes, but not tested.

# Contact me

If for any reason, you want to communicate with me, feel free to send me an e-mail to the address: $noel.kneib@laposte.net$

Thank you for reading this / using this, and have fun.
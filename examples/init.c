#include <stdio.h>
#include <garbage/garbage.h>


int main(int argc, char** argv){

    // Initialization
    GarbageInit();
    if (GarbageInited() == false) {
        // If not inited we can leave safely, because we don't keep partially inited garbage
        exit(1);
    }

    // Declare the GarbageFree function to launch on exit.
    atexit(GarbageFree);


    return EXIT_SUCCESS;
}


// Define the cleaners. Here we just display a message and free the pointer, but it can be a specific free function such as SDL_DestroyTexture
void callbackToFreeInt(int* data){
    printf("Freed by the function callbackToFreeInt\n");
    // Do something
    // Free manually some elements
    // Process some verifications etc.

    if(data == NULL){
        return;
    }

    free(data);
    data = NULL;
}


void callbackToFreeFloat(float* data){
    printf("Freed by the function callbackToFreeFloat\n");
    // Do something
    // Free manually some elements
    // Process some verifications etc.

    if(data == NULL){
        return;
    }

    free(data);
    data = NULL;
}


void callbackToFreeStr(char* data){
    printf("Freed by the function callbackToFreeStr\n");
    // Do something
    // Free manually some elements
    // Process some verifications etc.

    if(data == NULL){
        return;
    }

    free(data);
    data = NULL;
}

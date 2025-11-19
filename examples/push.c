#include <garbage/garbage.h>

// Define some function to free different kind of pointers
void callbackToFreeInt(int*);
void callbackToFreeFloat(float*);
void callbackToFreeStr(char*);


int main(int argc, char** argv){

    // Initialize the garbage
    GarbageInit();

    // Check if the garbage has been inited
    if(GarbageInited() == false){
        printf("Error on garbage initialization\n");
        exit(1);
    }

    // Free the garbage
    atexit(GarbageFree);

    // Create some pointers
    int* ptrA = (int*)calloc(1, sizeof(int));
    float* ptrB = (float*)calloc(1, sizeof(float));
    char* ptrC = (char*)calloc(20, sizeof(char));

    // Push some pointers without any callback
    bool result = false;
    result = GarbagePush(ptrA, NULL);
    // We should test each push to prevent some leaking because of a data not pushed
    if (!result) {
        printf("Error on pushing into garbage\n");
        free(ptrA);
    }

    result = false;
    result = GarbagePush(ptrB, NULL);
    if (!result) {
        printf("Error on pushing into garbage\n");
        free(ptrB);
    }

    result = false;
    result = GarbagePush(ptrC, NULL);
    if (!result) {
        free(ptrC);
    }

    // Declare more pointers
    int* ptrD = (int*) calloc(1, sizeof(int));
    float* ptrE = (float*)calloc(1, sizeof(float));
    char* ptrF = (char*)calloc(20, sizeof(char));

    // Push more pointers with a callback
    result = false;
    result = GarbagePush(ptrD, (cleaner)callbackToFreeInt);
    if (!result) {
        printf("Error on pushing into garbage\n");
        free(ptrD);
    }

    result = false;
    result = GarbagePush(ptrE, (cleaner)callbackToFreeFloat);
    if (!result) {
        printf("Error on pushing into garbage\n");
        free(ptrE);
    }

    result = false;
    result = GarbagePush(ptrF, (cleaner)callbackToFreeStr);
    if (!result) {
        printf("Error on pushing into garbage\n");
        free(ptrF);
    }

    return EXIT_SUCCESS;
}

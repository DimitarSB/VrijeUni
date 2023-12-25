#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct obj_metadata {
    size_t size;
    struct obj_metadata *next;
    struct obj_metadata *prev;
    int is_free;
};

size_t neededBytesForMeta = sizeof(struct obj_metadata);
struct obj_metadata *start = NULL;
struct obj_metadata *prevList = NULL;

void createNewElement(void *currentBreak, size_t newSize) {
    
    if(start == NULL){
        start = currentBreak;
        start->is_free = 0;
        start->size = newSize;
        start->prev = NULL;
        start->next = NULL;
    }
    else{
        struct obj_metadata *current = start;
        while (current->next != NULL) {
            prevList = current;
            current = current->next;
        }
        current->next = currentBreak;
        current->next->is_free = 0;
        current->next->size = newSize;
        current->next->next = NULL;
        current->prev = prevList;
    }
}

void split(size_t newSize, struct obj_metadata *current) {

    size_t leftoverSize = current->size - newSize;
    
    if (leftoverSize < neededBytesForMeta){ // Do I have enough for meta?:
        return;
    }

    void *currentLocation = (void *)current + neededBytesForMeta + newSize;

    // Connect blocks:
    struct obj_metadata *newElement = (void *)currentLocation;
    newElement->is_free = 1;
    newElement->size = leftoverSize - neededBytesForMeta;
    newElement->prev = current;
    newElement->next = current->next;

    if (current->next != NULL) {
        current->next->prev = newElement;
    }
    current->next = newElement;
    current->size = newSize;
}

void *searchForGap(size_t newSize){

    void *result = NULL;
    if(start == NULL){
        return result;
    }

    if(start->is_free == 1 && start->size >= newSize){
        if(start->size > newSize){
            split(newSize, start);
        }
        start->is_free = 0;
        return start;
    }
    else{
        struct obj_metadata *current = start;
        while (!(current->next == NULL)){
            current = current->next;
            if(current->is_free == 1 && current->size >= newSize){
                if(current->size > newSize){
                    split(newSize, current);
                }
                current->is_free = 0;
                return current;
            }
        }
    }
    return result;
}

void *mymalloc(size_t size){
    
    void *currentBreak = sbrk(0);
    if(size == 0){
        currentBreak = NULL;
        return currentBreak;
    }

    if(size % 8 != 0){
        int neededMem = size / 8 + 1;
        size = 8 * neededMem;
    }

    void *result = searchForGap(size);
    if(result != NULL){
        currentBreak = (void *)result + neededBytesForMeta;
    }
    else{
        currentBreak = sbrk(neededBytesForMeta + size);
        createNewElement(currentBreak, size);
        currentBreak = (void *)currentBreak + neededBytesForMeta;
    }
    return currentBreak;
}

void *mycalloc(size_t nmemb, size_t size){
    
    void *current = NULL;
    current = mymalloc(size * nmemb);
    memset(current, 0, size * nmemb);
    return current; 
}

void merge(struct obj_metadata *current){

    if(current->next != NULL && current->next->is_free == 1){
        current->size = current->size + current->next->size + neededBytesForMeta;
        if(current->next->next != NULL){
            current->next->next->prev = current;
            current->next = current->next->next;
        }
    }

    if(current->prev != NULL && current->prev->is_free == 1){
            current->prev->size = current->prev->size + current->size + neededBytesForMeta;
            if(current->next != NULL){
            current->next->prev = current->prev;
            current->prev->next = current->next;
        } 
    }

}

void release(struct obj_metadata *current){
    
    // Go to the last free block and then free it: 
    if (current != NULL && current->is_free == 1) {
        struct obj_metadata *checkLastBlock = current;
        while (checkLastBlock->next != NULL && checkLastBlock->next->is_free == 1) {
            checkLastBlock = checkLastBlock->next;
        }

        if (checkLastBlock->next == NULL) {
            if (brk(checkLastBlock) == 0) {
                checkLastBlock->next = NULL;
                // current = checkLastBlock;
                // Disconnect them properly: 
                if (checkLastBlock->prev != NULL) {
                    checkLastBlock->prev->next = NULL;
                } else start = NULL;

            } else {
                perror("brk is not working correctly!");
            }
        }

    }
}

void myfree(void *ptr) {

    if (ptr == NULL) {
        return;
    }

    void *metaDataPtr = (void *)ptr - neededBytesForMeta;
    struct obj_metadata *current = start;

    while (current != NULL) {
        if (current == metaDataPtr) {
            current->is_free = 1;
            break;
        }
        current = current->next;
    }
    merge(current);
    //release(current);
}

void *myrealloc(void *ptr, size_t size){
    
    struct obj_metadata *newSpace;
    struct obj_metadata *ptrElement = (void *)ptr - neededBytesForMeta;
    if(size == 0){
        myfree(ptr);
        return NULL;
    }
    if(ptr == NULL){
        newSpace = mymalloc(size);
        return newSpace;
    }

    if(ptrElement->size >= size){
        return ptr;
    }
    else{
        newSpace = mymalloc(size);
        if(newSpace == NULL){
            return NULL;
        }
        memcpy(newSpace, ptr, ptrElement->size);
        myfree(ptr);
    }
    return newSpace;
}

/*
 * Enable the code below to enable system allocator support for your allocator.
 * Doing so will make debugging much harder (e.g., using printf may result in
 * infinite loops).
 */
#if 1
void *malloc(size_t size) { return mymalloc(size); }
void *calloc(size_t nmemb, size_t size) { return mycalloc(nmemb, size); }
void *realloc(void *ptr, size_t size) { return myrealloc(ptr, size); }
void free(void *ptr) { myfree(ptr); }
#endif
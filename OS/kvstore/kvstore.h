#ifndef KVSTORE_H
#define KVSTORE_H

#include "common.h"
#include "hash.h"
#include <pthread.h>


struct user_item {
    pthread_mutex_t selfLock;
    // Add your fields here.
    // You can access this structure from ht_item's user field defined in hash.h
};

struct user_ht {

    // Add your fields here.
    // You can access this structure from the hashtable_t's user field define in has.h
};

#endif

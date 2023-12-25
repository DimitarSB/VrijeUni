#include <semaphore.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

#include "server_utils.h"
#include "common.h"
#include "request_dispatcher.h"
#include "hash.h"
#include "kvstore.h"

// DO NOT MODIFY THIS.
// ./check.py assumes the hashtable has 256 buckets.
// You should initialize your hashtable with this capacity.
#define HT_CAPACITY 256
#define NUM_OF_WORKERS 16

pthread_mutex_t queueLock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t queueCond;
struct conn_info* queue[256];
int requestInQueue = 0;

int ht_init(){
    ht = malloc(sizeof(hashtable_t));
    if(!ht){
        return -1;
    }
    ht->items = calloc(HT_CAPACITY, sizeof(hash_item_t*));
    if(ht->items == NULL){
        return -1;
    }
    ht->capacity = HT_CAPACITY;
    ht->user = (void*)malloc(sizeof(struct user_ht));
    return 0;
}

int set_request(int socket, struct request *request){
    size_t expected_len = request->msg_len;

    hash_item_t *item = NULL;
    char *key = request->key;
    
    // 1. Get entry or create one if it does not exist.
    unsigned int h = hash(key) % ht->capacity;
    hash_item_t *entry = ht->items[h];
    
    //Find the item:
    pr_info("Before while loop item[h]: %s \n", entry ? entry->key : "NULL");
    while(entry != NULL){
        if(!strcmp(entry->key, key)){
            item = entry;
            break;
        }
        entry = entry->next;
    }
    
    if (item == NULL){
        hash_item_t *new_item = malloc(sizeof(hash_item_t));
        new_item->user = (void*)malloc(sizeof(struct user_item));
        new_item->prev = NULL;
        new_item->next = ht->items[h];

        if(ht->items[h] != NULL){
            ht->items[h]->prev = new_item;
        }

        ht->items[h] = new_item;
        new_item->key = malloc(strlen(key) + 1);
        strcpy(new_item->key, key);
        item = new_item;
        pthread_mutex_init(&item->user->selfLock, NULL);
    }

    // Note: take into account critical regions.
    // Another thread entering this function should not be able to get the entry again.

    size_t len = 0;
    size_t remainingSize = expected_len;
    int chunk_size = 1024;
    // if(pthread_mutex_trylock(&item->user->selfLock) == 0){
    //     pr_info("The error number is:_____________________________ %i\n", errno);
    
        pthread_mutex_lock(&item->user->selfLock);

        //Allocate memory for the entire thing:
        item->value = malloc(expected_len + 1);
        item->value[expected_len] = '\0';
        item->value_size = expected_len;


        while (len < expected_len) {
            // 2. Read the payload from the socket
            char receivedBuf[1024];
            pr_info("Total Bytes to read: %zu", expected_len);

            //Establish chunk:
            if(remainingSize > 1024)
                chunk_size = 1024;
            else chunk_size = remainingSize;

            int receivedInfo = read_payload(socket, request, chunk_size, receivedBuf);
            //pr_info("Recieved Bytes %i at rotation : %i", receivedInfo, rotations);

            //Error if we read less then expected:
            if(receivedInfo != chunk_size){
                ht->items[h] = ht->items[h]->next;
                free(item->value);
                free(item->key);
                free(item);
                check_payload(socket, request, expected_len);
                send_response(socket, STORE_ERROR, 0, NULL);
                
                request->connection_close = 1;
                return -1;
            }
            memcpy(item->value + len, receivedBuf, chunk_size);

            len += receivedInfo;
            remainingSize = remainingSize - receivedInfo;

            // Note: Clients may send a partial chunk of the payload: do not not wait
            // for the full data to be available before writing in the hashtable entry.

            // 3. Write the partial payload on the entry
        }
        pthread_mutex_unlock(&item->user->selfLock);
        pthread_mutex_destroy(&item->user->selfLock);
    // }
    // else{
    //     check_payload(socket, request, expected_len);
    //     send_response(socket, KEY_ERROR, 0, NULL);
    //     request->connection_close = 1;
    //     return -1;
    // }
    // 4. Insert the entry in the store.
    // This allow other threads to read the entry.

    // It checks if the payload has been fully received .
    // It also reads the last char of the request which should be '\n'
    check_payload(socket, request, expected_len);
    send_response(socket, OK, 0, NULL);

    // pr_info("Read %zu / %zu\n", len, expected_len);

    // Optionally you can close the connection
    // You should do it ONLY on errors:
    // request->connection_close = 1;
    return len;
}

int get_request(int socket, struct request *request){
    
    hash_item_t *item = NULL;
    char *key = request->key;
    
    unsigned int h = hash(key) % ht->capacity;
    hash_item_t *e = ht->items[h];

    //Find the item:
    while(e != NULL){
        if(!strcmp(e->key, key)){
            item = e;
            break;
        }
        e = e->next;
    }
    
    if(item == NULL){
        send_response(socket, KEY_ERROR, 0, NULL);
        return -1;
    }

    pthread_mutex_lock(&item->user->selfLock);
    send_response(socket, OK, item->value_size, item->value);
    pthread_mutex_unlock(&item->user->selfLock);
    return 0;
}

int del_request(int socket, struct request *request){

    hash_item_t *item = NULL;
    char *key = request->key;

    unsigned int h = hash(key) % ht->capacity;
    hash_item_t *e = ht->items[h];

    //Find the item:
    while(e != NULL){
        if(!strcmp(e->key, key)){
            item = e;
            break;
        }
        e = e->next;
    }

    if(item == NULL){
        send_response(socket, KEY_ERROR, 0, NULL);
        request->connection_close = 1;
        return -1;
    }

    //pthread_mutex_lock(&item->user->selfLock);
    if(item->prev != NULL && item->next != NULL){
        item->prev->next = item->next;
        item->next->prev = item->prev;      
    }
    else if(item->next != NULL){;
        ht->items[h] = item->next;
        item->next->prev = NULL;
    }
    else if(item->prev != NULL){
        item->prev->next = NULL;
    }
    else ht->items[h] = NULL;
    //pthread_mutex_unlock(&item->user->selfLock); 

    free(item->value);
    free(item->key);
    free(item);
    send_response(socket, OK, 0, NULL);  
     
    return 0;
}

void *main_job(void *arg)
{
    pr_info("Got the job!\n");
    int method;
    struct conn_info *conn_info = arg;
    struct request *request = allocate_request();
    request->connection_close = 0;

    pr_info("Starting new session from %s:%d\n",
        inet_ntoa(conn_info->addr.sin_addr),
        ntohs(conn_info->addr.sin_port));

    do {
        method = recv_request(conn_info->socket_fd, request);

        // Insert your operations here
        switch (method) {
        case SET:
            set_request(conn_info->socket_fd, request);
            break;
        case GET:
            get_request(conn_info->socket_fd, request);
            break;
        case DEL:
            del_request(conn_info->socket_fd, request);
            break;
        case RST:
            free(ht);
            ht_init();
            // ./check.py issues a reset request after each test
            // to bring back the hashtable to a known state.
            // Implement your reset command here.
            send_response(conn_info->socket_fd, OK, 0, NULL);
            break;
        case STAT:
            break;
        }

        if (request->key) {
            free(request->key);
        }

    } while (!request->connection_close);

    close_connection(conn_info->socket_fd);
    free(request);
    free(conn_info);
    return (void *)NULL;
}

void* waitingRoom(){
    while(1){
        struct conn_info* nextRequest;
        pthread_mutex_lock(&queueLock);   
        while(requestInQueue == 0){
            pthread_cond_wait(&queueCond, &queueLock);
        }
        nextRequest = queue[0];

        //Smashing the queue:
        for(int i = 0; i < requestInQueue; i++){
            queue[i] = queue[i + 1];
        }
        requestInQueue--;
    
        pthread_mutex_unlock(&queueLock);
        main_job(nextRequest);
    }
}

int main(int argc, char *argv[])
{
    int listen_sock;
    listen_sock = server_init(argc, argv);

    // Initialize your hashtable.
    if(ht_init() != 0){
        perror("Hashtable init error!\n");
        exit(1);
    }
    // @see kvstore.h for hashtable struct declaration

    pthread_t workers[NUM_OF_WORKERS];
    //Create the threads:
    for(int i = 0; i < NUM_OF_WORKERS; i++){
        if(pthread_create(&workers[i], NULL, &waitingRoom, NULL) != 0){
            perror("Error when creating threads! \n");
            exit(-1);
        }
    }

    for (;;) {
        struct conn_info *conn_info =
            calloc(1, sizeof(struct conn_info));
        if (accept_new_connection(listen_sock, conn_info) < 0) {
            error("Cannot accept new connection");
            free(conn_info);
            continue;
        }
        //main_job(conn_info);

        //Add into the queue + protection:
        pthread_mutex_lock(&queueLock);

        queue[requestInQueue] = conn_info;
        requestInQueue++;
        pthread_cond_signal(&queueCond);
        
        pthread_mutex_unlock(&queueLock);

    }

    //Destroy the threads:
    for(int i = 0; i < NUM_OF_WORKERS; i++){
        if(pthread_join(workers[i], NULL) != 0){
            perror("Error when destroying threads! \n");
            exit(-1);
        }
    }

    //Destroy the locks and cond:
    pthread_mutex_destroy(&queueLock);
    pthread_cond_destroy(&queueCond);
    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <dispatch/dispatch.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

dispatch_semaphore_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i;
        dispatch_semaphore_wait(empty, DISPATCH_TIME_FOREVER);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        dispatch_semaphore_signal(full);
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        dispatch_semaphore_wait(full, DISPATCH_TIME_FOREVER);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        dispatch_semaphore_signal(empty);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    empty = dispatch_semaphore_create(BUFFER_SIZE);
    full = dispatch_semaphore_create(0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    dispatch_release(empty);
    dispatch_release(full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
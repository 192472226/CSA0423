#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;                 // shared variable
pthread_mutex_t lock;            // mutex lock

void* increment(void *arg) {
    for (int i = 0; i < 5; i++) {

        pthread_mutex_lock(&lock);  // enter critical section

        counter++;
        printf("Thread %d incremented counter to %d\n",
               *((int*)arg), counter);

        pthread_mutex_unlock(&lock); // exit critical section
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // initialize mutex
    pthread_mutex_init(&lock, NULL);

    // create two threads
    pthread_create(&t1, NULL, increment, &id1);
    pthread_create(&t2, NULL, increment, &id2);

    // wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // destroy mutex
    pthread_mutex_destroy(&lock);

    printf("\nFinal counter value = %d\n", counter);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;              // semaphore for writer
pthread_mutex_t mutex;  // mutex to protect readcount
int readcount = 0;      // number of active readers
int data = 0;           // shared data

void *reader(void *arg) {
    int id = *((int*)arg);

    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wrt);  // first reader blocks writers
        }
        pthread_mutex_unlock(&mutex);

        // reading section
        printf("Reader %d reads data = %d\n", id, data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wrt);  // last reader releases writer
        }
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void *writer(void *arg) {
    int id = *((int*)arg);

    while (1) {
        sem_wait(&wrt);  // writer enters
        data++;          // writing
        printf("Writer %d writes data = %d\n", id, data);
        sem_post(&wrt);  // writer exits
        sleep(2);
    }
}

int main() {
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // create reader threads
    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);
    pthread_create(&r[2], NULL, reader, &rid[2]);

    // create writer threads
    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&w[1], NULL, writer, &wid[1]);

    // join threads
    pthread_join(r[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    pthread_join(w[0], NULL);
    pthread_join(w[1], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}


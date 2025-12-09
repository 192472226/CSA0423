#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* myThread(void* arg) {
    int id = ((int)arg);
    printf("Thread %d started. TID = %lu\n", id, pthread_self());

    // Return a message safely
    char* msg = "Thread completed.";
    pthread_exit((void*)msg);

    return NULL;   // Avoid warnings
}

int main() {
    pthread_t t1, t2;
    int a = 1, b = 2;
    void* exitMessage;

    // pthread_create
    if (pthread_create(&t1, NULL, myThread, (void*)&a) != 0) {
        printf("Error creating Thread 1.\n");
        exit(1);
    }

    if (pthread_create(&t2, NULL, myThread, (void*)&b) != 0) {
        printf("Error creating Thread 2.\n");
        exit(1);
    }

    // pthread_join
    pthread_join(t1, &exitMessage);
    printf("Joined Thread 1 ? %s\n", (char*)exitMessage);

    pthread_join(t2, &exitMessage);
    printf("Joined Thread 2 ? %s\n", (char*)exitMessage);

    // pthread_equal
    if (pthread_equal(t1, t2))
        printf("Thread 1 and Thread 2 are EQUAL.\n");
    else
        printf("Thread 1 and Thread 2 are NOT equal.\n");

    return 0;
}

 #include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    int shmid;
    char *shared_memory;

    // Create a unique key
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create shared memory segment of size 1024 bytes
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach shared memory to process
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Creating a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child writes a message to shared memory
        printf("Child: Writing message to shared memory...\n");
        sprintf(shared_memory, "Hello from Child Process!");
        printf("Child: Message written.\n");

        // Child detaches
        if (shmdt(shared_memory) == -1) {
            perror("shmdt (child)");
            exit(EXIT_FAILURE);
        }
    }
    else {
        // Parent waits to ensure child writes first
        sleep(1);

        printf("Parent: Reading message from shared memory...\n");
        printf("Parent: Message = %s\n", shared_memory);

        // Parent detaches
        if (shmdt(shared_memory) == -1) {
            perror("shmdt (parent)");
            exit(EXIT_FAILURE);
        }

        // Destroy the shared memory
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}


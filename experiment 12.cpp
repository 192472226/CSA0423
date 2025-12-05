#include <windows.h>
#include <iostream>

using namespace std;

#define NUM_PHILOSOPHERS 5

HANDLE forks[NUM_PHILOSOPHERS];
HANDLE threads[NUM_PHILOSOPHERS];

DWORD WINAPI philosopher(LPVOID param)
{
    int id = (int)(intptr_t)param;   // ? Safe 64-bit compatible cast

    while (true)
    {
        cout << "Philosopher " << id << " is thinking..." << endl;
        Sleep(1000);

        // Pick fork (left)
        WaitForSingleObject(forks[id], INFINITE);

        // Pick fork (right)
        WaitForSingleObject(forks[(id + 1) % NUM_PHILOSOPHERS], INFINITE);

        cout << "Philosopher " << id << " is eating..." << endl;
        Sleep(1000);

        // Release forks
        ReleaseMutex(forks[id]);
        ReleaseMutex(forks[(id + 1) % NUM_PHILOSOPHERS]);

        cout << "Philosopher " << id << " finished eating." << endl;
    }

    return 0;
}

int main()
{
    // Create forks (mutexes)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        forks[i] = CreateMutex(NULL, FALSE, NULL);

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        threads[i] = CreateThread(
            NULL,
            0,
            philosopher,
            (LPVOID)(intptr_t)i,   // ? Correct pointer-safe cast
            0,
            NULL
        );
    }

    // Wait forever
    WaitForMultipleObjects(NUM_PHILOSOPHERS, threads, TRUE, INFINITE);

    return 0;
}



#include <iostream>
#include <windows.h>

using namespace std;

// Function for Thread 1
DWORD WINAPI ThreadFunc1(LPVOID lpParam) {
    for (int i = 1; i <= 5; i++) {
        cout << "Thread 1: Count = " << i << endl;
        Sleep(1000); // Sleep 1 second
    }
    return 0;
}

// Function for Thread 2
DWORD WINAPI ThreadFunc2(LPVOID lpParam) {
    for (int i = 1; i <= 5; i++) {
        cout << "Thread 2: Count = " << i << endl;
        Sleep(1000); // Sleep 1 second
    }
    return 0;
}

int main() {
    // Create thread handles
    HANDLE hThread1, hThread2;

    // Create two threads
    hThread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
    hThread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);

    // Wait for both threads to finish
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    // Close thread handles
    CloseHandle(hThread1);
    CloseHandle(hThread2);

    cout << "Both threads finished execution." << endl;

    return 0;
}


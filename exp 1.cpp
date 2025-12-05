 #include <windows.h>
#include <iostream>
using namespace std;

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    cout << "Parent PID: " << GetCurrentProcessId() << endl;

    if(CreateProcess(NULL, (LPSTR)"notepad.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        cout << "Child PID: " << pi.dwProcessId << endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        cout << "Process creation failed" << endl;
    }

    return 0;
}


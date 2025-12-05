#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    HANDLE hPipe;
    char buffer[1024];
    DWORD bytesRead;

    cout << "Waiting for client connection..." << endl;

    hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\MyPipe"),
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cout << "Error creating pipe." << endl;
        return 1;
    }

    ConnectNamedPipe(hPipe, NULL);

    ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);
    buffer[bytesRead] = '\0';

    cout << "Received from client: " << buffer << endl;

    CloseHandle(hPipe);
    return 0;
}


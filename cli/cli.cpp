#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

void sendToDaemon(const string &cmd) {
    HANDLE pipe = CreateFileA("\\\\.\\pipe\\NumberPipe",
                              GENERIC_READ | GENERIC_WRITE,
                              0, NULL, OPEN_EXISTING, 0, NULL);
    if (pipe == INVALID_HANDLE_VALUE) {
        cout << "Daemon not running!\n";
        return;
    }

    DWORD written;
    WriteFile(pipe, cmd.c_str(), cmd.size() + 1, &written, NULL);

    char buf[512];
    DWORD read;
    if (ReadFile(pipe, buf, 512, &read, NULL)) cout << buf << "\n";

    CloseHandle(pipe);
}

int main() {
    while (true) {
        cout << "\n1.Insert 2.Delete 3.Print 4.Exit\nChoice: ";
        int ch;
        cin >> ch;

        if (ch == 1) {
            int n;
            cout << "Number: ";
            cin >> n;
            sendToDaemon("INSERT " + to_string(n));
        } else if (ch == 2) {
            int n;
            cout << "Number: ";
            cin >> n;
            sendToDaemon("DELETE " + to_string(n));
        } else if (ch == 3) {
            sendToDaemon("PRINT");
        } else if (ch == 4) {
            break;
        } else cout << "Invalid choice\n";
    }
    return 0;
}

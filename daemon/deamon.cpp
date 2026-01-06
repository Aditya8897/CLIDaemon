#include <windows.h>
#include <iostream>
#include <map>
#include <string>
#include <ctime>

using namespace std;

map<int, time_t> numbers;
HANDLE mutex;

int main()
{
    mutex = CreateMutex(NULL, FALSE, NULL);
    cout << "Daemon started...\n";

    while (true)
    {
        HANDLE pipe = CreateNamedPipeA("\\\\.\\pipe\\NumberPipe",
                                       PIPE_ACCESS_DUPLEX,
                                       PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                                       PIPE_UNLIMITED_INSTANCES,
                                       512, 512, 0, NULL);
        if (pipe == INVALID_HANDLE_VALUE)
            continue;

        ConnectNamedPipe(pipe, NULL);

        char buf[256];
        DWORD read;
        ReadFile(pipe, buf, 256, &read, NULL);
        string cmd = buf;

        cout << "[RECV] " << cmd << "\n";

        string reply = "OK";

        WaitForSingleObject(mutex, INFINITE);

        if (cmd.find("INSERT") == 0)
        {
            int n = atoi(cmd.c_str() + 7);
            if (n <= 0)
                reply = "Error: Only positive numbers allowed";
            else if (numbers.count(n))
                reply = "Error: Number already exists";
            else
            {
                numbers[n] = time(NULL);
                reply = "Inserted: " + to_string(n);
            }
        }
        else if (cmd.find("DELETE") == 0)
        {
            int n = atoi(cmd.c_str() + 7);
            if (numbers.erase(n))
                reply = "Deleted: " + to_string(n);
            else
                reply = "Error: Number not found";
        }
        else if (cmd == "PRINT")
        {
            reply = "";
            for (auto p : numbers)
                reply += to_string(p.first) + " | " + to_string(p.second) + "\n";
            if (reply.empty())
                reply = "No numbers stored";
        }
        else if (cmd == "DELETEALL")
        {
            numbers.clear();
            reply = "Deleted all numbers";
        }
        else
            reply = "Error: Unknown command";

        ReleaseMutex(mutex);

        cout << reply << "\n\n";

        DWORD written;
        WriteFile(pipe, reply.c_str(), reply.size() + 1, &written, NULL);
        CloseHandle(pipe);
    }

    CloseHandle(mutex);
    return 0;
}

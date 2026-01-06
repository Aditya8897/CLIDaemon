# CLIDaemonCLI-Daemon IPC Project
This is a C++ project that demonstrates Inter-Process Communication (IPC) using Windows Named Pipes. The system consists of a background daemon that stores data and a CLI tool that interacts with it.

How it Works
The project is split into two executables:

Daemon: Acts as the server. It uses a std::map to store numbers and their timestamps. It uses a Mutex to ensure data safety.

CLI: Acts as the client. It provides a menu for the user to send commands (Insert, Delete, Print) to the Daemon via a Named Pipe.

Getting Started
Prerequisites
CMake (to generate build files)

MinGW (g++ compiler)

PowerShell

Quick Run (Automation)
I have included a PowerShell script to handle everything automatically. Just run: .\automate.ps1

This script will:

Create the build folder.

Compile both applications.

Launch the Daemon in a new window.

Start the CLI in your current window.
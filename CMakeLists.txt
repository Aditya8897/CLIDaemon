cmake_minimum_required(VERSION 3.10)
project(ReliaQuestProject)

set(CMAKE_CXX_STANDARD 17)

# CLI application banayein
add_executable(cli_app cli/cli.cpp)

# Daemon application banayein
add_executable(daemon_app daemon/deamon.cpp)
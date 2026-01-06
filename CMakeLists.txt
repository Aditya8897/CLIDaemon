cmake_minimum_required(VERSION 3.10)
project(ReliaQuestProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(cli_app cli/cli.cpp)

add_executable(daemon_app daemon/deamon.cpp)
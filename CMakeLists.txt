cmake_minimum_required(VERSION 3.17)
project(prefork_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(prefork_server main.cpp server.cpp handler.cpp parser.cpp client.cpp)
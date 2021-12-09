cmake_minimum_required(VERSION 3.21)
project(caos)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(caos
        4/1_tests.cpp
        4/3_tests.cpp
        4/5.cpp
        5/1.c
        5/2.c
        5/3.c
        cw/1.cpp
        cw/3.cpp
        cw/5.cpp)

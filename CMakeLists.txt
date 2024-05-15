cmake_minimum_required(VERSION 3.27)
project(m2 C)

set(CMAKE_C_STANDARD 17)

add_executable(m2 main.c
        char_freq.c
        char_freq.h)

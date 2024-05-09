cmake_minimum_required(VERSION 3.26)
project(Lab_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_19 main.c
        file/file.h
        file/file.c
        file/matrix.h
        file/matrix.c)


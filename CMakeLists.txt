cmake_minimum_required(VERSION 3.26)
project(Lab_19 C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab_19 main.c
        file/file.h
        file/file.c
        file/matrix.h
        file/matrix.c
        file/string_.h
        file/string_.c
        file/string_processing.h
        file/string_processing.c
        file/polynom.h
        file/polynom.c
        file/vector.h
        file/vector.c
        file/sportsman.h
        file/sportsman.c
        file/product.h
        file/product.c
        file_tests/file_tests.h
        file_tests/file_tests.c
        lab_20/lab_20.h
        lab_20/lab_20.c
        lab_20/domen.h
        lab_20/domen.c
        lab_20_test/lab_20_test.h
        lab_20_test/lab_20_test.c
        lab_20/knot.h
        lab_20/knot.c)


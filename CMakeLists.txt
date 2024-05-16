cmake_minimum_required(VERSION 3.26)
project(Laboratory_20 C)

set(CMAKE_C_STANDARD 11)

add_executable(Laboratory_20
        main.c
        libs/algorithms/algorithms.c
        libs/algorithms/algorithms.h
        libs/matrix/matrix.h
        libs/matrix/matrix.c
        libs/tests/tests.h
        libs/tests/tests.c)

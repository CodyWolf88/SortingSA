cmake_minimum_required(VERSION 4.1)
project(SortingSA C)

set(CMAKE_C_STANDARD 23)

add_executable(SortingSA main.c
        array_generators.c
        array_generators.h
        sorting_algorithms.c
        sorting_algorithms.h
)

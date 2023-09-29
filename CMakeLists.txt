cmake_minimum_required(VERSION 3.14)

project(Lab1 LANGUAGES C)

add_compile_options(
        -g
#        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wenum-compare
        -Wfloat-equal
        -Wredundant-decls
        -Wsign-conversion
    )

if(NOT CMAKE_C_EXTENSIONS)
    set(CMAKE_C_EXTENSIONS OFF)
endif()


add_executable(lab1_main src/main.c)

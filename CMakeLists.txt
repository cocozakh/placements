cmake_minimum_required(VERSION 3.16)

project(placements C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(placements main.c)

if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(placements PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()
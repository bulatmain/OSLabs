# Main
cmake_minimum_required(VERSION 3.14)

project(Lab2 LANGUAGES C CXX)

# Variables
option(LAB2_TESTING "Включить модульное тестирование" ON)

# Header
add_library(Lab2_headers INTERFACE)
target_include_directories(Lab2_headers INTERFACE include)
add_library(Lab2::headers ALIAS Lab2_headers)

# Source
add_library(Lab2_source STATIC
    src/thread_queue.c
    src/planner.c
)
target_link_libraries(Lab2_source PUBLIC Lab2_headers)
target_compile_features(Lab2_source PRIVATE c_std_17)

add_library(Lab2::source ALIAS Lab2_source)


# Executive
add_executable(exec exec/main.c)

target_link_libraries(exec Lab2::source)

# Auxiliary
if(NOT LAB2_TESTING)
    message(STATUS "Тестирование выключено")
else()
    add_subdirectory(test)
endif()


cmake_minimum_required(VERSION 3.16)

add_compile_options(--coverage)
add_link_options(--coverage)

project(oop_lab_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_library(lab1 lab1.h lab1.cpp)

add_subdirectory(tests)

link_libraries(lab1)

add_executable(main main.cpp)
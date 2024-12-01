cmake_minimum_required(VERSION 3.10 REQUIRED)

set(PROJECT_NAME "AdventOfCode24")
project(${PROJECT_NAME})

set(CMAKE_C_STANDARD 89)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE src)
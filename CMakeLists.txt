cmake_minimum_required(VERSION 3.26)
project(AdventOfCode24)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
endif()

# Include necessary directories
include_directories(src)

file(GLOB MAIN_SOURCE
        src/*.c
)

#file(GLOB_RECURSE APP_SOURCES
#        src/...
#)

add_executable(AdventOfCode24 ${MAIN_SOURCE})#${APP_SOURCES})
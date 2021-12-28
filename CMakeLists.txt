cmake_minimum_required(VERSION 3.22.1)

project(sentinel VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SENTINEL_SOURCES
        src/*.cpp)
add_executable(sentinel ${SENTINEL_SOURCES})
target_include_directories(sentinel PRIVATE include)

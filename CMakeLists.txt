cmake_minimum_required(VERSION 3.12.0)

project(rayster VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE RAYSTER_SOURCES
        src/*.cpp)
add_executable(rayster ${RAYSTER_SOURCES})
target_include_directories(rayster PRIVATE inc)

cmake_minimum_required(VERSION 3.12.0)

project(reddere VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(REDDERE_SOURCES
        src/main.cpp
        src/framebuffer.cpp
        src/geometry.cpp
        src/renderer.cpp
        src/texture.cpp
        src/transform.cpp
        src/model.cpp
        src/material.cpp)
add_executable(reddere ${REDDERE_SOURCES})
target_include_directories(reddere PRIVATE
        include
        shaders
)

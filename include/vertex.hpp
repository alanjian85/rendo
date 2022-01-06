#ifndef RAYSTER_VERTEX_HPP
#define RAYSTER_VERTEX_HPP

#include "vector4.hpp"
#include "vertex_data.hpp"

namespace rayster {
    struct vertex {
        vector4 pos;
        vertex_data data;
    };
}

#endif
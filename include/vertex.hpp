#ifndef RAYSTER_VERTEX_HPP
#define RAYSTER_VERTEX_HPP

#include "vertex_data.hpp"
#include "vector3.hpp"

namespace rayster {
    struct vertex {
        vector3 pos;
        vertex_data data;
    };
}

#endif
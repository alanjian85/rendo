#ifndef RAYSTER_VERTEX_HPP
#define RAYSTER_VERTEX_HPP

#include "vertex_data.hpp"
#include "position3.hpp"

namespace rayster {
    struct vertex {
        position3 pos;
        vertex_data data;
    };
}

#endif
#ifndef RAYSTER_VERTEX_HPP
#define RAYSTER_VERTEX_HPP

#include "vector.hpp"

namespace rayster {
    struct vertex_data {
        vector3 pos;

        vertex_data& operator*=(double rhs) {
            pos *= rhs;
            return *this;
        }
    };

    inline vertex_data operator+(const vertex_data& lhs, const vertex_data& rhs) {
        return {
            lhs.pos + rhs.pos
        };
    }

    inline vertex_data operator*(const vertex_data& lhs, double rhs) {
        return {
            lhs.pos * rhs
        };
    }

    inline vertex_data operator*(double lhs, const vertex_data& rhs) {
        return rhs * lhs;
    }

    struct vertex {
        vector4 pos;
        vertex_data data;
    };
}

#endif
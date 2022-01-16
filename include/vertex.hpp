#ifndef RAYSTER_VERTEX_HPP
#define RAYSTER_VERTEX_HPP

#include "vector.hpp"

namespace rayster {
    struct vertex_data {
        vector2 uv;

        vertex_data& operator*=(double rhs) {
            uv *= rhs;
            return *this;
        }
    };

    inline vertex_data operator+(const vertex_data& lhs, const vertex_data& rhs) {
        return {
            lhs.uv + rhs.uv
        };
    }

    inline vertex_data operator*(const vertex_data& lhs, double rhs) {
        return {
            lhs.uv * rhs  
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
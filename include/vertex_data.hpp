#ifndef RAYSTER_VERTEX_DATA_HPP
#define RAYSTER_VERTEX_DATA_HPP

#include "color.hpp"
#include "vector2.hpp"

namespace rayster {
    struct vertex_data {
        vector2 uv;
    };

    inline vertex_data operator+(const vertex_data& lhs, const vertex_data& rhs) noexcept {
        return {
            lhs.uv + rhs.uv
        };
    }

    inline vertex_data operator*(const vertex_data& lhs, double rhs) noexcept {
        return {
            lhs.uv * rhs  
        };
    }

    inline vertex_data operator*(double lhs, const vertex_data& rhs) noexcept {
        return rhs * lhs;
    }
}

#endif
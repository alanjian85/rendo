#ifndef RAYSTER_VERTEX_DATA_HPP
#define RAYSTER_VERTEX_DATA_HPP

#include "color.hpp"

namespace rayster {
    struct vertex_data {
        color_rgb color;
    };

    inline vertex_data operator+(const vertex_data& lhs, const vertex_data& rhs) noexcept {
        return {
            lhs.color + rhs.color
        };
    }

    inline vertex_data operator*(const vertex_data& lhs, double rhs) noexcept {
        return {
            lhs.color * rhs  
        };
    }

    inline vertex_data operator*(double lhs, const vertex_data& rhs) noexcept {
        return rhs * lhs;
    }
}

#endif
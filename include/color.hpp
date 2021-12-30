#ifndef RAYSTER_COLOR_HPP
#define RAYSTER_COLOR_HPP

namespace rayster {
    struct color_rgb {
        double r;
        double g;
        double b;
    };

    inline color_rgb operator+(color_rgb lhs, color_rgb rhs) noexcept {
        return {lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b};
    }

    inline color_rgb operator*(color_rgb lhs, double rhs) noexcept {
        return {lhs.r * rhs, lhs.g * rhs, lhs.b * rhs};
    }

    inline color_rgb operator*(double lhs, color_rgb rhs) noexcept {
        return rhs * lhs;
    }
}

#endif

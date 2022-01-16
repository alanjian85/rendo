#ifndef RAYSTER_COLOR_HPP
#define RAYSTER_COLOR_HPP

namespace rayster {
    struct color_rgba {
        double r;
        double g;
        double b;
        double a;
    };

    inline color_rgba operator+(color_rgba lhs, color_rgba rhs) {
        return {lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a};
    }

    inline color_rgba operator*(color_rgba lhs, double rhs) {
        return {lhs.r * rhs, lhs.g * rhs, lhs.b * rhs, lhs.a * rhs};
    }

    inline color_rgba operator*(double lhs, color_rgba rhs) {
        return rhs * lhs;
    }

    inline color_rgba operator*(color_rgba lhs, color_rgba rhs) {
        return {lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a};
    }
}

#endif

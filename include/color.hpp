#ifndef BOX_COLOR_HPP
#define BOX_COLOR_HPP

#include <cmath>

namespace box {
    struct color_rgba;

    struct color_rgb {
        double r, g, b;

        color_rgb() = default;
        color_rgb(double d_)
            : r(d_), g(d_), b(d_)
        {

        }
        color_rgb(double r_, double g_, double b_)
            : r(r_), g(g_), b(b_)
        {

        }
        color_rgb(color_rgba);

        color_rgb& operator+=(color_rgb rhs) {
            r += rhs.r;
            g += rhs.g;
            b += rhs.b;
            return *this;
        }

        color_rgb& operator*=(color_rgb rhs) {
            r *= rhs.r;
            g *= rhs.g;
            b *= rhs.b;
            return *this;
        }
    };

    inline color_rgb operator+(color_rgb lhs, color_rgb rhs) {
        return {lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b};
    }

    inline color_rgb operator*(color_rgb lhs, color_rgb rhs) {
        return {lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b};
    }

    inline color_rgb operator*(color_rgb lhs, double rhs) {
        return {lhs.r * rhs, lhs.g * rhs, lhs.b * rhs};
    }
    
    inline color_rgb operator/(color_rgb lhs, color_rgb rhs) {
        return {lhs.r / rhs.r, lhs.g / rhs.g, lhs.b / rhs.b};
    }

    inline color_rgb pow(color_rgb x, color_rgb y) {
        return {
            std::pow(x.r, y.r),
            std::pow(x.g, y.g),
            std::pow(x.b, y.b)
        };
    }

    struct color_rgba {
        double r, g, b, a;

        color_rgba() = default;
        color_rgba(double r_, double g_, double b_, double a_)
            : r(r_), g(g_), b(b_), a(a_)
        {

        }
        color_rgba(color_rgb rgb, double a_)
            : r(rgb.r), g(rgb.g), b(rgb.b), a(a_)
        {

        }
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

    inline color_rgb::color_rgb(color_rgba rgba)
        : r(rgba.r), g(rgba.g), b(rgba.b)
    {

    }
}

#endif

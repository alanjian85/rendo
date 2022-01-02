#ifndef RAYSTER_CUBE_HPP
#define RAYSTER_CUBE_HPP

#include <array>

#include "triangle.hpp"

namespace rayster {
    class cube {
    public:
        using iterator = std::array<triangle, 12>::iterator;
        using const_iterator = std::array<triangle, 12>::const_iterator;
        
        cube(double size) noexcept;

        iterator begin() noexcept {
            return triangles_.begin();
        }

        iterator end() noexcept {
            return triangles_.end();
        }

        const_iterator begin() const noexcept {
            return triangles_.begin();
        }
        
        const_iterator end() const noexcept {
            return triangles_.end();
        }
    private:
        std::array<triangle, 12> triangles_;
    };
}

#endif
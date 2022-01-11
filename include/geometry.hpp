#ifndef RAYSTER_GEOMETRY_HPP
#define RAYSTER_GEOMETRY_HPP

#include <array>
#include <cstdlib>

#include "aabb.hpp"
#include "vector.hpp"
#include "vector.hpp"
#include "vertex.hpp"

namespace rayster {
    struct triangle {
        using size_type = std::size_t;

        vertex a;
        vertex b;
        vertex c;

        vertex& operator[](size_type index) noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        const vertex& operator[](size_type index) const noexcept {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 barycentric(vector2 p) const noexcept;
        aabb2 bounding_box() const noexcept;
    };

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
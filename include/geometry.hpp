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

        vertex& operator[](size_type index) {
            return index == 0 ? a : index == 1 ? b : c;
        }

        const vertex& operator[](size_type index) const {
            return index == 0 ? a : index == 1 ? b : c;
        }

        vector3 barycentric(vector2 p) const;
        aabb2 bounding_box() const;
    };

    class cube {
    public:
        using iterator = std::array<triangle, 12>::iterator;
        using const_iterator = std::array<triangle, 12>::const_iterator;
        
        cube(double size);

        iterator begin() {
            return triangles_.begin();
        }

        iterator end() {
            return triangles_.end();
        }

        const_iterator begin() const {
            return triangles_.begin();
        }
        
        const_iterator end() const {
            return triangles_.end();
        }
    private:
        std::array<triangle, 12> triangles_;
    };
}

#endif
#ifndef RAYSTER_MODEL_HPP
#define RAYSTER_MODEL_HPP

#include <cstdlib>
#include <string>
#include <vector>

#include "vector.hpp"

namespace rayster {
    class model {
    public:
        void load(const std::string& path);

        auto num_faces() const {
            return face_vertices.size() / 3;
        }

        vector4 get_vertex(int face, int n) const {
            return vertices_[face_vertices[face * 3 + n]];
        }
    private:
        std::vector<vector4> vertices_;
        std::vector<vector3> tex_coords_;
        std::vector<vector3> normals_;

        std::vector<std::size_t> face_vertices; 
        std::vector<std::size_t> face_normals_;
        std::vector<std::size_t> face_tex_coords_;
    };
}

#endif
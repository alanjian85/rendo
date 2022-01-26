#include "model.hpp"
using namespace box;

#include <fstream>
#include <sstream>
#include <stdexcept>

void model::load(const std::filesystem::path& path) {
    auto dir = path.parent_path();

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open model file " + path.string());

    for (std::string line; std::getline(file, line);) {
        std::istringstream stream(line);

        std::string attrib;
        stream >> attrib;

        if (attrib == "v") {
            vector3 v;
            stream >> v.x >> v.y >> v.z;
            vertices_.push_back(v);
        } else if (attrib == "vt") {
            vector2 uv;
            stream >> uv.x >> uv.y;
            uvs_.push_back(uv);
        } else if (attrib == "vn") {
            vector3 n;
            stream >> n.x >> n.y >> n.z;
            normals_.push_back(n);
        } else if (attrib == "f") {
            char delim;
            int v, t, n;
            while (stream >> v) {
                face_vertices_.push_back(v - 1);
                
                if (!uvs_.empty()) {
                    stream >> delim >> t;
                    face_uvs_.push_back(t - 1);
                }

                if (!normals_.empty()) {
                    if (uvs_.empty())
                        stream >> delim;

                    stream >> delim >> n;
                    face_normals_.push_back(n - 1);
                }
            }
        } else if (attrib == "mtllib") {
            std::string relative_path;
            stream >> relative_path;

            mtllib_.load(dir / relative_path);
        } else if (attrib == "usemtl") {
            std::string mat;
            stream >> mat;

            materials_.emplace_back(face_vertices_.size(), &mtllib_[mat]);
        }
    }
}
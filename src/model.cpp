#include "model.hpp"
using namespace rayster;

#include <fstream>
#include <sstream>

void model::load(const std::string& path) {
    std::ifstream file(path);
    for (std::string line; std::getline(file, line);) {
        std::istringstream stream(line);

        std::string attrib;
        stream >> attrib;

        if (attrib == "v") {
            vector4 v;
            stream >> v.x >> v.y >> v.z;
            if (!(stream >> v.w)) {
                v.w = 1;
            }
            vertices_.push_back(v);
        } else if (attrib == "vt") {
            vector3 t;
            stream >> t.x;
            if (!(stream >> t.y)) {
                t.y = 0;
            } else if (!(stream >> t.z)) {
                t.z = 0;
            }
            tex_coords_.push_back(t);
        } else if (attrib == "vn") {
            vector3 n;
            stream >> n.x >> n.y >> n.z;
            normals_.push_back(n);
        } else if (attrib == "f") {
            char delim;
            int v, t, n;
            while (stream >> v) {
                face_vertices_.push_back(v - 1);
                
                if (!tex_coords_.empty()) {
                    stream >> delim >> t;
                    face_tex_coords_.push_back(t - 1);
                }

                if (!normals_.empty()) {
                    if (tex_coords_.empty())
                        stream >> delim;

                    stream >> delim >> n;
                    face_normals_.push_back(n - 1);
                }
            }
        }
    }
}
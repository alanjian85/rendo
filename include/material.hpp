#ifndef BOX_MATERIAL_HPP
#define BOX_MATERIAL_HPP

#include <string>
#include <filesystem>
#include <map>

#include "color.hpp"
#include "texture.hpp"

namespace box {
    struct material {
        color_rgba ambient;
        color_rgba diffuse;
        color_rgba specular;
        color_rgba emission;
        double shininess;
        double refraction;
        double opacity;
        int illum;
        texture diffuse_map;
    };

    class material_library {
    public:
        void load(const std::filesystem::path& path);

        const material& operator[](const std::string& mat) const {
            return materials_.at(mat);
        }
    private:
        std::map<std::string, material> materials_;
    };
}

#endif
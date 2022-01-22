#ifndef RAYSTER_MATERIAL_HPP
#define RAYSTER_MATERIAL_HPP

#include <string>
#include <filesystem>
#include <map>

#include "color.hpp"
#include "texture.hpp"

namespace rayster {
    struct material {
        color_rgb ambient;
        color_rgb diffuse;
        color_rgb specular;
        color_rgb emission;
        double shininess;
        double refraction;
        double opacity;
        int illum;
        texture diffuse_map;
    };

    class material_library {
    public:
        void load(const std::filesystem::path& path);
    private:
        std::map<std::string, material> materials_;
    };
}

#endif
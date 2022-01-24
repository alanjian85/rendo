#include "material.hpp"
using namespace box;

#include <fstream>
#include <sstream>
#include <stdexcept>

void material_library::load(const std::filesystem::path& path) {
    auto dir = path.parent_path();

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open material library file " + path.string());

    material* mat = nullptr;
    for (std::string line; std::getline(file, line);) {
        std::istringstream stream(line);
        
        std::string attrib;
        stream >> attrib;        
        if (attrib == "newmtl") {
            std::string name;
            stream >> name;

            mat = &materials_[name];
        } else if (attrib == "Ns") {
            stream >> mat->shininess;
        } else if (attrib == "Ka") {
            stream >> mat->ambient.r >> mat->ambient.g >> mat->ambient.b;
        } else if (attrib == "Kd") {
            stream >> mat->diffuse.r >> mat->diffuse.g >> mat->diffuse.b;
        } else if (attrib == "Ks") {
            stream >> mat->specular.r >> mat->specular.g >> mat->specular.b;
        } else if (attrib == "Ke") {
            stream >> mat->emission.r >> mat->emission.g >> mat->emission.b;
        } else if (attrib == "Ni") {
            stream >> mat->refraction;
        } else if (attrib == "d") {
            stream >> mat->opacity;
        } else if (attrib == "illum") {
            stream >> mat->illum;
        } else if (attrib == "map_Kd") {
            std::string relative_path;
            stream >> relative_path;

            mat->diffuse_map.load(dir / relative_path);
        }
    }
}
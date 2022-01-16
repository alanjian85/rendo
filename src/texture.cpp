#include "texture.hpp"
using namespace rayster;

#include <algorithm>
#include <cmath>
#include <fstream>

void texture::load(const std::string& path) {
    std::ifstream file(path);

    std::string format;
    std::getline(file, format);

    texture::size_type width, height;
    file >> width >> height;
    resize(width, height);

    if (format == "P1") {
        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                char c;
                file >> c;

                if (c == '0')
                    (*this)(x, y) = {0, 0, 0, 1};
                else if (c == '1')
                    (*this)(x, y) = {1, 1, 1, 1};
            }
        } while (y > 0);
    } else if (format == "P2") {
        int max_value;
        file >> max_value;
        
        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                int color;
                file >> color;

                auto t = static_cast<double>(color) / max_value;
                (*this)(x, y) = {t, t, t, 1};
            }
        } while (y > 0);
    } else if (format == "P3"){
        int max_value;
        file >> max_value;

        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                int r, g, b;
                file >> r >> g >> b;

                (*this)(x, y) = {
                    static_cast<double>(r) / max_value,
                    static_cast<double>(g) / max_value,
                    static_cast<double>(b) / max_value,
                    1
                };
            }
        } while (y > 0);
    } else if (format == "P5") {
        int max_value;
        file >> max_value;
        
        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                auto color = static_cast<unsigned char>(file.get());

                auto t = static_cast<double>(color) / max_value;
                (*this)(x, y) = {t, t, t, 1};
            }
        } while (y > 0);
    } else if (format == "P6") {
        int max_value;
        file >> max_value;

        file.ignore(1);

        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                unsigned char r, g, b;
                r =  file.get(); g = file.get(); b = file.get();

                (*this)(x, y) = {
                    static_cast<double>(r) / max_value,
                    static_cast<double>(g) / max_value,
                    static_cast<double>(b) / max_value,
                    1
                };
            }
        } while (y > 0);
    }
}

color_rgba sampler2::operator()(vector2 uv) const {
    switch (wrap()) {
    case wrapping::repeat:
        if (uv.x < 0 || uv.x > 1)
            uv.x = uv.x - std::floor(uv.x);
        if (uv.y < 0 || uv.y > 1)
            uv.y = uv.y - std::floor(uv.y);
        break;
    case wrapping::repeat_mirrored:
        if (static_cast<int>(uv.x) % 2 == 0) {
            uv.x = uv.x - std::floor(uv.x);
        } else {
            uv.x = std::ceil(uv.x) - uv.x;
        }
        if (static_cast<int>(uv.y) % 2 == 0) {
            uv.y = uv.y - std::floor(uv.y);
        } else {
            uv.y = std::ceil(uv.y) - uv.y;
        }
    case wrapping::clamp_to_edge:
        uv.x = std::clamp(uv.x, 0.0, 1.0);
        uv.y = std::clamp(uv.y, 0.0, 1.0);
        break;
    case wrapping::clamp_to_border:
        if (uv.x < 0 || uv.x > 1 || uv.y < 0 || uv.y > 1) {
            return border();
        }
    }

    auto x = static_cast<texture::size_type>(uv.x * (tex_->width() - 1));
    auto y = static_cast<texture::size_type>(uv.y * (tex_->height() - 1));
    return (*tex_)(x, y);
}
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

color_rgba sampler2::operator()(vector3 tex_coord) const {
    if (!tex_)
        return {0, 0, 0, 0};

    switch (wrap()) {
    case wrapping::repeat:
        if (tex_coord.x < 0 || tex_coord.x > 1)
            tex_coord.x = tex_coord.x - std::floor(tex_coord.x);
        if (tex_coord.y < 0 || tex_coord.y > 1)
            tex_coord.y = tex_coord.y - std::floor(tex_coord.y);
        break;
    case wrapping::repeat_mirrored:
        if (static_cast<int>(tex_coord.x) % 2 == 0) {
            tex_coord.x = tex_coord.x - std::floor(tex_coord.x);
        } else {
            tex_coord.x = std::ceil(tex_coord.x) - tex_coord.x;
        }
        if (static_cast<int>(tex_coord.y) % 2 == 0) {
            tex_coord.y = tex_coord.y - std::floor(tex_coord.y);
        } else {
            tex_coord.y = std::ceil(tex_coord.y) - tex_coord.y;
        }
    case wrapping::clamp_to_edge:
        tex_coord.x = std::clamp(tex_coord.x, 0.0, 1.0);
        tex_coord.y = std::clamp(tex_coord.y, 0.0, 1.0);
        break;
    case wrapping::clamp_to_border:
        if (tex_coord.x < 0 || tex_coord.x > 1 || tex_coord.y < 0 || tex_coord.y > 1) {
            return border();
        }
    }

    auto x = static_cast<texture::size_type>(tex_coord.x * (tex_->width() - 1));
    auto y = static_cast<texture::size_type>(tex_coord.y * (tex_->height() - 1));
    return (*tex_)(x, y);
}

color_rgba sampler_cube::operator()(vector3 tex_coord) const {
    auto x = tex_coord.x;
    auto y = tex_coord.y;
    auto z = tex_coord.z;
    
    auto ax = std::abs(x);
    auto ay = std::abs(y);
    auto az = std::abs(z);

    sampler2 sampler;
    sampler.set_border(border_);

    auto u = 0.0;
    auto v = 0.0;

    if (ax > ay && ax > az) {
        u = (1 - z / x) / 2;
        if (x > 0) {
            sampler.bind_texture(*right_);
            v = (1 - y / x) / 2;
        } else {
            sampler.bind_texture(*left_);
            v = (1 + y / x) / 2;
        }
        sampler.set_wrap(wrap_s_);
    } else if (ay > ax && ay > az) {
        v = (1 + z / y) / 2;
        if (y > 0) {
            sampler.bind_texture(*top_);
            u = (1 + x / y) / 2;
        } else {
            sampler.bind_texture(*bottom_);
            u = (1 - x / y) / 2;
        }
        sampler.set_wrap(wrap_t_);
    } else if (az > ax && az > ay) {
        u = (1 + x / z) / 2;
        if (z > 0) {
            sampler.bind_texture(*back_);
            v = (1 - y / z) / 2;
        } else {
            sampler.bind_texture(*front_);
            v = (1 + y / z) / 2;
        }
        sampler.set_wrap(wrap_r_);
    }
    
    return sampler({u, v});
}
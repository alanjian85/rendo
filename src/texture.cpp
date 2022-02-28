#include "texture.hpp"
using namespace box;

#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>

void texture::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open texture file " + path);

    int max_value, depth;

    for (std::string line; std::getline(file, line);) {
        std::istringstream stream(line);
        
        std::string attrib;
        stream >> attrib;

        if (attrib == "WIDTH") {
            stream >> width_;
        } else if (attrib == "HEIGHT") {
            stream >> height_;
        } else if (attrib == "DEPTH") {
            stream >> depth;
        } else if (attrib == "MAXVAL") {
            stream >> max_value;
        } else if (attrib == "ENDHDR") {
            break;
        }
    }

    pixels_.resize(width_ * height_);
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            switch (depth) {
                case 1: {
                    unsigned char r;
                    r = file.get();

                    (*this)(x, y) = {
                        static_cast<double>(r) / max_value,
                        static_cast<double>(r) / max_value,
                        static_cast<double>(r) / max_value,
                        1
                    };

                    break;
                }
                case 2: {
                    unsigned char r, a;
                    r = file.get(); a = file.get();

                    (*this)(x, y) = {
                        static_cast<double>(r) / max_value,
                        static_cast<double>(r) / max_value,
                        static_cast<double>(r) / max_value,
                        static_cast<double>(a) / max_value
                    };

                    break;
                }
                case 3: {
                    unsigned char r, g, b;
                    r = file.get(); g = file.get(); b = file.get();

                    (*this)(x, y) = {
                        static_cast<double>(r) / max_value,
                        static_cast<double>(g) / max_value,
                        static_cast<double>(b) / max_value,
                        1
                    };

                    break;
                }
                case 4: {
                    unsigned char r, g, b, a;
                    r = file.get(); g = file.get(); b = file.get(); a = file.get();

                    (*this)(x, y) = {
                        static_cast<double>(r) / max_value,
                        static_cast<double>(g) / max_value,
                        static_cast<double>(b) / max_value,
                        static_cast<double>(a) / max_value
                    };
                    
                    break;
                }
            }
        }
    }
}

color_rgba sampler2::operator()(vector2 uv) const {
    if (!tex_)
        return {0, 0, 0, 0};

    switch (wrap()) {
    case wrapping::repeat:
        double temp;
        uv.x = std::modf(uv.x, &temp);
        if (uv.x < 0)
            uv.x = 1 + uv.x;
        uv.y = std::modf(uv.y, &temp);
        if (uv.y < 0)
            uv.y = 1 + uv.x;
        break;
    case wrapping::repeat_mirrored:
        double intx, inty;
        uv.x = std::modf(uv.x, &intx);
        if (uv.x < 0)
            uv.x = 1 + uv.x;
        if (static_cast<int>(intx) % 2 == 1)
            uv.x = 1 - uv.x;
        uv.y = std::modf(uv.y, &inty);
        if (uv.y < 0)
            uv.y = 1 + uv.x;
        if (static_cast<int>(inty) % 2 == 1)
            uv.y = 1 - uv.y;
    case wrapping::clamp_to_edge:
        uv.x = std::clamp(uv.x, 0.0, 1.0);
        uv.y = std::clamp(uv.y, 0.0, 1.0);
        break;
    case wrapping::clamp_to_border:
        if (uv.x < 0 || uv.x > 1 || uv.y < 0 || uv.y > 1) {
            return border();
        }
    }

    auto x = std::clamp(static_cast<int>(uv.x * (tex_->width() - 1)), 0, tex_->width() - 1);
    auto y = std::clamp(static_cast<int>((1 - uv.y) * (tex_->height() - 1)), 0, tex_->height() - 1);
    return (*tex_)(x, y);
}

color_rgba sampler_cube::operator()(vector3 uvw) const {
    auto x = uvw.x;
    auto y = uvw.y;
    auto z = uvw.z;
    
    auto ax = std::abs(x);
    auto ay = std::abs(y);
    auto az = std::abs(z);

    sampler2 sampler;
    sampler.set_border(border_);

    auto u = 0.0;
    auto v = 0.0;

    if (ax > ay && ax > az) {
        v = (y / ax - 1) / 2;
        if (x > 0) {
            sampler.bind_texture(*right_);
            u = (-z / ax + 1) / 2;
        } else {
            sampler.bind_texture(*left_);
            u = (z / ax + 1) / 2;
        }
        sampler.set_wrap(wrap_s_);
    } else if (ay > ax && ay > az) {
        u = (x / ay + 1) / 2;
        if (y > 0) {
            sampler.bind_texture(*top_);
            v = (-z / ay - 1) / 2;
        } else {
            sampler.bind_texture(*bottom_);
            v = (z / ay - 1) / 2;
        }
        sampler.set_wrap(wrap_t_);
    } else if (az > ax && az > ay) {
        v = (y / az - 1) / 2;
        if (z > 0) {
            sampler.bind_texture(*front_);
            u = (x / az + 1) / 2;
        } else {
            sampler.bind_texture(*back_);
            u = (-x / az + 1) / 2;
        }
        sampler.set_wrap(wrap_r_);
    }
    
    return sampler(u, v);
}
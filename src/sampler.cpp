#include "sampler.hpp"
using namespace rayster;

#include <algorithm>
#include <cmath>

color_rgba sampler::operator()(const texture& tex, vector2 v) const noexcept {
    switch (wrap_) {
    case wrapping::repeat:
        if (v.x < 0 || v.x > 1)
            v.x = v.x - std::floor(v.x);
        if (v.y < 0 || v.y > 1)
            v.y = v.y - std::floor(v.y);
        break;
    case wrapping::repeat_mirrored:
        if (static_cast<int>(v.x) % 2 == 0) {
            v.x = v.x - std::floor(v.x);
        } else {
            v.x = std::ceil(v.x) - v.x;
        }
        if (static_cast<int>(v.y) % 2 == 0) {
            v.y = v.y - std::floor(v.y);
        } else {
            v.y = std::ceil(v.y) - v.y;
        }
    case wrapping::clamp_to_edge:
        v.x = std::clamp(v.x, 0.0, 1.0);
        v.y = std::clamp(v.y, 0.0, 1.0);
        break;
    case wrapping::clamp_to_border:
        if (v.x < 0 || v.x > 1 || v.y < 0 || v.y > 1) {
            return border_;
        }
    }

    auto x = static_cast<texture::size_type>(v.x * (tex.width() - 1));
    auto y = static_cast<texture::size_type>(v.y * (tex.height() - 1));
    return tex(x, y);
}
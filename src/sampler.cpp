#include "sampler.hpp"
using namespace rayster;

#include <cmath>

color_rgb sampler::operator()(const texture& tex, vector2 v) const noexcept {
    switch (wrap_) {
    case wrapping::repeat:
        if (v.x < 0 || v.x > 1)
            v.x = v.x - std::floor(v.x);
        if (v.y < 0 || v.y > 1)
            v.y = v.y - std::floor(v.y);
        break;
    }

    auto x = static_cast<texture::size_type>(v.x * (tex.width() - 1));
    auto y = static_cast<texture::size_type>(v.y * (tex.height() - 1));
    return tex(x, y);
}
#include "sampler2.hpp"
using namespace rayster;

#include <algorithm>
#include <cmath>

color_rgba sampler2::operator()(vector2 uv) const noexcept {
    switch (wrap_) {
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
            return border_;
        }
    }

    auto x = static_cast<texture::size_type>(uv.x * (tex_->width() - 1));
    auto y = static_cast<texture::size_type>(uv.y * (tex_->height() - 1));
    return (*tex_)(x, y);
}
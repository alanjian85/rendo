#include "framebuffer.hpp"
using namespace rayster;

#include <algorithm>

std::ostream& rayster::operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept {
    lhs << "P3\n";
    lhs << rhs.width() << ' ' << rhs.height() << '\n';
    lhs << "255\n";

    auto y = rhs.height();
    do {
        --y;
        for (auto x = 0; x < rhs.width(); ++x) {
            auto r = static_cast<int>(rhs(x, y).color.r * 255);
            auto g = static_cast<int>(rhs(x, y).color.g * 255);
            auto b = static_cast<int>(rhs(x, y).color.b * 255);

            lhs << std::clamp(r, 0, 255) << ' ';
            lhs << std::clamp(g, 0, 255) << ' ';
            lhs << std::clamp(b, 0, 255) << '\n';
        }
    } while (y > 0);

    return lhs;
}
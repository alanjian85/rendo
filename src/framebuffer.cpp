#include "framebuffer.hpp"
using namespace rayster;

#include <algorithm>

std::ostream& rayster::operator<<(std::ostream& lhs, const framebuffer& rhs) noexcept {
    lhs << "P3\n";
    lhs << rhs.width() << ' ' << rhs.height() << '\n';
    lhs << "255\n";

    for (auto p : rhs) {
            auto r = static_cast<int>(p.color.r * 255);
            auto g = static_cast<int>(p.color.g * 255);
            auto b = static_cast<int>(p.color.b * 255);
    
            lhs << std::clamp(r, 0, 255) << ' ';
            lhs << std::clamp(g, 0, 255) << ' ';
            lhs << std::clamp(b, 0, 255) << ' ';
    }
    
    return lhs;
}

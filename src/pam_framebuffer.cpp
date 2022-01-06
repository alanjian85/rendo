#include "pam_framebuffer.hpp"
using namespace rayster;

#include <algorithm>

std::ostream& rayster::operator<<(std::ostream& lhs, const pam_framebuffer& rhs) noexcept {
    lhs << "P7\n";
    lhs << "WIDTH " << rhs.width() << '\n';
    lhs << "HEIGHT " << rhs.height() << '\n';
    lhs << "DEPTH 4\n";
    lhs << "MAXVAL 255\n";
    lhs << "TUPLTYPE RGB_ALPHA\n";
    lhs << "ENDHDR\n";

    auto y = rhs.height();
    do {
        --y;
        for (auto x = 0; x < rhs.width(); ++x) {
            auto r = static_cast<int>(rhs(x, y).color.r * 255);
            auto g = static_cast<int>(rhs(x, y).color.g * 255);
            auto b = static_cast<int>(rhs(x, y).color.b * 255);
            auto a = static_cast<int>(rhs(x, y).color.a * 255);

            r = std::clamp(r, 0, 255);
            g = std::clamp(g, 0, 255);
            b = std::clamp(b, 0, 255);
            a = std::clamp(a, 0, 255);

            lhs.put(r); lhs.put(g); lhs.put(b); lhs.put(a);
        }
    } while (y > 0);

    return lhs;
}
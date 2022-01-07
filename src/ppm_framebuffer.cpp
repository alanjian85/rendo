#include "ppm_framebuffer.hpp"
using namespace rayster;

#include <algorithm>
#include <fstream>

void ppm_framebuffer::write(const std::string& path) const {
    std::ofstream file(path);
    file << "P3\n";
    file << width() << ' ' << height() << '\n';
    file << "255\n";

    auto y = height();
    do {
        --y;
        for (auto x = 0; x < width(); ++x) {
            auto r = static_cast<int>((*this)(x, y).color.r * 255);
            auto g = static_cast<int>((*this)(x, y).color.g * 255);
            auto b = static_cast<int>((*this)(x, y).color.b * 255);

            r = std::clamp(r, 0, 255);
            g = std::clamp(g, 0, 255);
            b = std::clamp(b, 0, 255);

            file << r << ' ';
            file << g << ' ';
            file << b << ' ';
        }
    } while (y > 0);
}
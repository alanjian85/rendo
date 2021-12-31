#include "texture.hpp"
using namespace rayster;

std::istream& rayster::operator>>(std::istream& lhs, texture& rhs) {
    std::string format;
    std::getline(lhs, format);

    texture::size_type width, height;
    lhs >> width >> height;
    rhs.resize(width, height);

    if (format == "P1") {
        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                char c;
                lhs >> c;

                if (c == '0')
                    rhs(x, y) = {0, 0, 0, 1};
                else if (c == '1')
                    rhs(x, y) = {1, 1, 1, 1};
            }
        } while (y > 0);
    } else if (format == "P2") {
        int max_value;
        lhs >> max_value;
        
        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                int color;
                lhs >> color;

                auto t = static_cast<double>(color) / max_value;
                rhs(x, y) = {t, t, t, 1};
            }
        } while (y > 0);
    } else if (format == "P3"){
        int max_value;
        lhs >> max_value;

        auto y = height;
        do {
            --y;
            for (texture::size_type x = 0; x < width; ++x) {
                int r, g, b;
                lhs >> r >> g >> b;

                rhs(x, y) = {
                    static_cast<double>(r) / max_value,
                    static_cast<double>(g) / max_value,
                    static_cast<double>(b) / max_value,
                    1
                };
            }
        } while (y > 0);
    }

    return lhs;
}
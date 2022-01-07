#include "texture.hpp"
using namespace rayster;

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
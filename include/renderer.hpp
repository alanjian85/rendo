#ifndef RAYSTER_RENDERER_HPP
#define RAYSTER_RENDERER_HPP

#include <fstream>
#include <string>

#include "framebuffer.hpp"
#include "triangle.hpp"

namespace rayster {
    class renderer {
    public:
        renderer()
            : fb_(800, 600)
        {

        }

        void clear(color_rgb color) noexcept {
            fb_.clear(color);
        }

        void write(const std::string& path) {
            std::ofstream file(path);
            file << fb_;
        }

        void draw_triangle(const triangle& tri) noexcept;
    private:
        framebuffer fb_;
    };
}

#endif
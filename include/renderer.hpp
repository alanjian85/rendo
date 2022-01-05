#ifndef RAYSTER_RENDERER_HPP
#define RAYSTER_RENDERER_HPP

#include <fstream>
#include <string>

#include "cube.hpp"
#include "framebuffer.hpp"
#include "shader.hpp"
#include "triangle.hpp"
#include "viewport.hpp"

namespace rayster {
    class renderer {
    public:
        renderer()
            : fb_(1024, 1024)
        {
            view_.min = {0, 0};
            view_.max = {1024, 1024};
            view_.near = 0;
            view_.far = 1;
        }

        void clear(color_rgba color) noexcept {
            fb_.clear(color);
        }

        void write(const std::string& path) {
            std::ofstream file(path);
            file << fb_;
        }

        const viewport& view() const noexcept {
            return view_;
        }

        void draw_triangle(triangle tri, shader& s) noexcept;
        
        void draw_cube(const cube& c, shader& s) noexcept {
            for (auto& tri : c) {
                draw_triangle(tri, s);
            }
        }
    private:
        framebuffer fb_;
        viewport view_;
    };
}

#endif
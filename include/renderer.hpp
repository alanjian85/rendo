#ifndef RAYSTER_RENDERER_HPP
#define RAYSTER_RENDERER_HPP

#include <fstream>
#include <memory>
#include <string>

#include "framebuffer.hpp"
#include "geometry.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace rayster {
    class renderer {
    public:
        renderer()
            : fb_(1024, 1024)
        {
            
        }

        void clear(color_rgba color) {
            fb_.clear(color);
        }

        void write(const std::string& path) {
            fb_.write(path);
        }

        double aspect() const {
            return fb_.aspect();
        }

        void render(int n, basic_shader& s);
    private:
        void render_triangle(triangle t, basic_shader& s);

        framebuffer fb_;
    };
}

#endif
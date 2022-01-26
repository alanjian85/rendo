#ifndef BOX_RENDERER_HPP
#define BOX_RENDERER_HPP

#include <fstream>
#include <memory>
#include <string>

#include "framebuffer.hpp"
#include "geometry.hpp"
#include "shader.hpp"
#include "model.hpp"

namespace box {
    enum class cull_type {
        none,
        front,
        back
    };

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

        void set_face_culling(cull_type cull) {
            face_culling_ = cull;
        }

        void enable_depth_writing() {
            depth_writing_ = true;
        }

        void disable_depth_writing() {
            depth_writing_ = false;
        }

        void render(int n, basic_shader& s);
    private:
        void render_triangle(triangle t, basic_shader& s);

        framebuffer fb_;

        bool depth_writing_ = true;
        cull_type face_culling_ = cull_type::none;
    };
}

#endif
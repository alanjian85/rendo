#ifndef BOX_RENDERER_HPP
#define BOX_RENDERER_HPP

#include <fstream>
#include <functional>
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
        using post_processor_type = std::function<color_rgba(vector2, pixel)>;

        renderer(framebuffer& fb)
            : fb_(fb)
        {

        }

        void set_face_culling(cull_type cull) {
            face_culling_ = cull;
        }

        void render(int n, basic_shader& s);

        void post_process(const post_processor_type& p);
    private:
        void render_triangle(triangle t, basic_shader& s);

        framebuffer& fb_;

        cull_type face_culling_ = cull_type::none;
    };
}

#endif
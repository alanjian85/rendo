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
        {
            fb_ = std::make_unique<ppm_framebuffer>(1024, 1024);
        }

        void clear(color_rgba color) {
            fb_->clear(color);
        }

        double aspect() const {
            return fb_->aspect();
        }

        void render(triangle t, shader& s);

        void render(const model& m, shader& s);
    private:
        std::unique_ptr<framebuffer> fb_;
    };
}

#endif
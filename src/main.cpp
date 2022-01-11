#include <fstream>

#include "renderer.hpp"
#include "sampler.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utility.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    basic_shader()
        : persp_(rad(45), 800.0 / 600.0, 0.1, 100.0),
          lookat_({0, 0, 3}, {0, 0, 0}, {0, 1, 0}),
          rotate_(rad(45), {1, 1, 1})
    {
        texture_.load("res/textures/texture.ppm");
        sampler_.bind_texture(texture_);
    }
    
    virtual vertex vert(const vertex& vert) override {
        return {persp_ * lookat_ * rotate_ * vert.pos, vert.data};
    }

    virtual color_rgba frag(const vertex_data& data) override {
        return sampler_(data.uv);
    }
private:
    texture texture_;
    sampler2 sampler_;
    persp persp_;
    lookat lookat_;
    rotate rotate_;
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    cube c(1);

    basic_shader s;
    render.draw_cube(c, s);

    render.fb().write("image.ppm");
}
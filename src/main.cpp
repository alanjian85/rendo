#include <fstream>

#include "lookat.hpp"
#include "renderer.hpp"
#include "rotate.hpp"
#include "sampler.hpp"
#include "texture.hpp"
#include "utility.hpp"
#include "persp.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    basic_shader()
        : persp_(rad(45), 800.0 / 600.0, 0.1, 100.0),
          lookat_({0, 0, 3}, {0, 0, 0}, {0, 1, 0}),
          rotate_(rad(45), {1, 1, 1})
    {
        std::ifstream tex_file("res/textures/texture.ppm", std::ios::binary);
        tex_file >> texture_;
        sampler_.wrap(wrapping::repeat_mirrored);
    }
    
    virtual vertex vert(const vertex& vert) override {
        return {persp_ * lookat_ * rotate_ * vert.pos, vert.data};
    }

    virtual color_rgba frag(const vertex_data& data) override {
        return sampler_(texture_, data.uv);
    }
private:
    texture texture_;
    sampler sampler_;
    persp persp_;
    lookat lookat_;
    rotate rotate_;
};

int main() {
  renderer render;
    render.clear({0.2, 0.3, 0.3, 1.0});

    cube c(1);

    basic_shader s;
    render.draw_cube(c, s);

    render.write("image.pam");
}
#include <fstream>

#include "renderer.hpp"
#include "sampler.hpp"
#include "texture.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    basic_shader() {
        std::ifstream tex_file("res/textures/texture.ppm");
        tex_file >> texture_;
        sampler_.wrap(wrapping::repeat_mirrored);
    }
    
    virtual vertex vert(const vertex& vert) override {
        return vert;
    }

    virtual color_rgb frag(const vertex_data& data) override {
        return sampler_(texture_, data.uv) * color_rgb{data.uv.x, data.uv.y, 0.25};
    }
private:
    texture texture_;
    sampler sampler_;
};

int main() {
    renderer render;
    render.clear({0.2, 0.3, 0.3});

    std::vector<triangle> triangles(2);
    triangles[0].a = {{-0.5,   0.5, 0}, {0, 1}};
    triangles[0].b = {{-0.5, -0.75, 0}, {0, 0}};
    triangles[0].c = {{ 0.5,  0.75, 0}, {1, 1}};

    triangles[1].a = {{-0.5, -0.75, 0}, {0, 0}};
    triangles[1].b = {{ 0.5,  0.75, 0}, {1, 1}};
    triangles[1].c = {{ 0.5, -0.5,  0}, {1, 0}};

    basic_shader s;
    for (auto& tri : triangles) {
        render.draw_triangle(tri, s);
    }

    render.write("image.ppm");
}
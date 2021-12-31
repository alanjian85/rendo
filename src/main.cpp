#include <fstream>

#include "renderer.hpp"
#include "texture.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    virtual vertex vert(const vertex& vert) override {
        return vert;
    }

    virtual color_rgb frag(const vertex_data& data) override {
        return data.color;
    }
};

int main() {
    renderer render;

    std::ifstream tex_file("texture.ppm");
    texture tex;
    tex_file >> tex;

    std::cout << tex.width() << ' ' << tex.height() << '\n';

    std::vector<triangle> triangles(2);
    triangles[0].a = {{-0.5,  0.5, 0}, {1, 0, 0}};
    triangles[0].b = {{-0.5, -0.5, 0}, {0, 1, 0}};
    triangles[0].c = {{ 0.5,  0.5, 0}, {0, 0, 1}};

    triangles[1].a = {{-0.5, -0.5, 0}, {1, 0, 0}};
    triangles[1].b = {{ 0.5,  0.5, 0}, {0, 1, 0}};
    triangles[1].c = {{ 0.5, -0.5, 0}, {0, 0, 1}};

    basic_shader s;
    for (auto& tri : triangles) {
        render.draw_triangle(tri, s);
    }

    render.write("image.ppm");
}
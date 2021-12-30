#include "renderer.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    virtual color_rgb fragment(const vertex_data& data) override {
        return data.color;
    }
};

int main() {
    renderer render;

    basic_shader s;
    triangle tri;
    tri.a = {{  0,   0, 0}, {1, 0, 0}};
    tri.b = {{400, 600, 0}, {0, 1, 0}};
    tri.c = {{800,   0, 0}, {0, 0, 1}};
    render.draw_triangle(tri, s);

    render.write("image.ppm");
}
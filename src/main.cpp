#include <fstream>
#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utility.hpp"
using namespace rayster;

class basic_shader : public shader {
public:
    basic_shader(const framebuffer& fb)
        : persp_(rad(45), fb.aspect(), 0.1, 100.0),
          lookat_({0, 0, 3}, {0, 0, 0}, {0, 1, 0}),
          rotate_(rad(0), {1, 1, 1})
    {
        
    }
    
    virtual vertex vert(const vertex& vert) override {
        return {persp_ * lookat_ * rotate_ * vert.pos, {vert.pos.x, vert.pos.y, vert.pos.z}};
    }

    virtual color_rgba frag(const vertex_data& data) override {
        return {1, 0, 0, 1};
    }
private:
    persp persp_;
    lookat lookat_;
    rotate rotate_;
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    vertex a, b, c;
    a.pos = {-1, -1, 0, 1};
    b.pos = { 0,  1, 0, 1};
    c.pos = { 1, -1, 0, 1};

    triangle t;
    t.a = &a;
    t.b = &b;
    t.c = &c;

    basic_shader s(render.fb());
    render.draw_triangle(t, s);

    render.fb().write("image.ppm");
}
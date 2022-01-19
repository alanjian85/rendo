#include <fstream>
#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "utility.hpp"
using namespace rayster;

class hello_shader : public shader {
public:
    hello_shader() {
        tri_[0] = {-0.5, -0.5, 0.0, 1.0};
        tri_[1] = { 0.0,  0.5, 0.0, 2.0};
        tri_[2] = { 0.5, -0.5, 0.0, 1.0};

        colors_[0] = {1.0, 0.0, 0.0, 1.0};
        colors_[1] = {0.0, 1.0, 0.0, 1.0};
        colors_[2] = {0.0, 0.0, 1.0, 1.0};
    }

    virtual vector4 vert(int n) override {
        return tri_[n];
    }

    virtual color_rgba frag(vector3 bar) override {
        return frag_lerp(colors_, bar);
    }
private:
    triangle tri_;
    color_rgba colors_[3];
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    hello_shader s;
    render.render(3, s);

    render.write("output/image.ppm");
}
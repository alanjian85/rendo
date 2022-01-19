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
        tri_.a = {-0.5, -0.5, 0.0, 1.0};
        tri_.b = { 0.0,  0.5, 0.0, 2.0};
        tri_.c = { 0.5, -0.5, 0.0, 1.0};
    }

    virtual vector4 vert(int n) override {
        return tri_[n];
    }

    virtual color_rgba frag(vector3 bar) override {
        return {bar.x, bar.y, bar.z, 1};
    }
private:
    triangle tri_;
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    hello_shader s;
    render.render(3, s);

    render.write("image.ppm");
}
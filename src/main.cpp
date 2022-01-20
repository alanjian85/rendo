#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace rayster;

class hello_shader : public shader {
public:
    hello_shader(const model& m) 
        : model_(m)
    {

    }

    virtual vector4 vert(int n) override {
        return model_.get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        return {1, 0, 0, 1};
    }
private:
    const model& model_;
};

int main() {
    renderer render;
    render.clear({0.627, 0.906, 0.898, 1.0});

    model m;
    m.load("res/models/cube.obj");

    std::cout << m.num_vertices() << '\n';

    hello_shader s(m);
    render.render(m.num_vertices(), s);

    render.write("output/image.ppm");
}
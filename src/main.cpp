#include <iostream>

#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace rayster;

class hello_shader : public shader {
public:
    hello_shader(double aspect, const model& m) 
        : model_(m),
          persp_(rad(45), aspect, 0.1, 100),
          lookat_({0, 0.075, 0.5}, {0, 0.075, 0}, {0, 1, 0}),
          rotate_(rad(45), {0, 1, 0})
    {

    }

    virtual vector4 vert(int n) override {
        v_normals[n % 3] = model_.get_normal(n);
        return persp_ * lookat_ * rotate_ * model_.get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto normal = frag_lerp(v_normals, bar);
        return {normal.x / 2 + 0.5, normal.y / 2 + 0.5, normal.z / 2 + 0.5, 1};
    }
private:
    const model& model_;

    persp persp_;
    lookat lookat_;
    rotate rotate_;

    vector3 v_normals[3];
};

int main() {
    renderer r;
    r.clear({0.627, 0.906, 0.898, 1.0});

    model m;
    m.load("res/models/bunny.obj");

    hello_shader s(r.aspect(), m);
    r.render(m.num_vertices(), s);

    r.write("output/image.ppm");
}
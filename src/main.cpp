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
          lookat_({0, 0, 6}, {0, 0, 0}, {0, 1, 0}),
          rotate_(rad(60), {1, 1, 1})
    {

    }

    virtual vector4 vert(int n) override {
        v_tex_coord_[n % 3] = model_.get_tex_coord(n);
        return persp_ * lookat_ * rotate_ * model_.get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto tex_coord = frag_lerp(v_tex_coord_, bar);
        return {tex_coord.x, tex_coord.y, tex_coord.z, 1};
    }
private:
    const model& model_;

    persp persp_;
    lookat lookat_;
    rotate rotate_;

    vector3 v_tex_coord_[3];
};

int main() {
    renderer r;
    r.clear({0.627, 0.906, 0.898, 1.0});

    model m;
    m.load("res/models/cube.obj");

    hello_shader s(r.aspect(), m);
    r.render(m.num_vertices(), s);

    r.write("output/image.ppm");
}
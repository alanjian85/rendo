#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace box;

class shader : public basic_shader {
public:
    shader(double aspect) 
        : aspect_(aspect),
          rotate_(make_rotate(rad(45), {1, 1, 1}))
    {
        camera_.pos.z = 6;
    }

    virtual vector4 vert(int n) override {
        v_tex_coords[n % 3] = model_->get_tex_coord(n);
        sampler_.bind_texture(model_->get_mat(n)->diffuse_map);
        return camera_.proj(aspect_) * camera_.view() * rotate_ * model_->get_vertex(n);
    }

    virtual color_rgba frag(vector3 bar) override {
        auto tex_coord = frag_lerp(v_tex_coords, bar);
        auto color = sampler_(tex_coord);
        return color;
    }
    
    void bind_model(const model& m) {
        model_ = &m;
    }
private:
    const model* model_;

    double aspect_;
    camera camera_;
    matrix4 rotate_;

    vector3 v_tex_coords[3];

    sampler2 sampler_;
};

int main() {
    try {
        renderer r;
        r.clear({0.90, 0.88, 0.84, 1.0});

        shader s(r.aspect());

        model cube("assets/models/cube.obj");
        s.bind_model(cube);
        r.render(cube.num_vertices(), s);

        r.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
#include <iostream>
#include <optional>

#include "camera.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "model.hpp"
#include "utility.hpp"
using namespace box;

class object_shader : public basic_shader {
public:
    object_shader(const camera& cam, double aspect, const sampler_cube& sampler_cube) 
        : camera_(cam),
          aspect_(aspect),
          sampler_(sampler_cube)
    {
        transform_ = make_translate({0, 0, 3});
    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(model_->get_vertex(n), 1);
        v_pos[n % 3] = vector3(pos);
        v_normal[n % 3] = model_->get_normal(n);
        return camera_.proj(aspect_) * camera_.view() * transform_ * pos;
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        auto normal = frag_lerp(v_normal, bar).normalize();
        auto cam_dir = (pos - camera_.pos).normalize();
        auto color = sampler_(reflect(cam_dir, normal));
        if (color.a < 0.1)
            return std::nullopt;
        return color;
    }
    
    void bind_model(const model& m) {
        model_ = &m;
    }
private:
    double aspect_;
    const camera& camera_;
    const model* model_;

    const sampler_cube& sampler_;

    matrix4 transform_;

    vector3 v_pos[3];
    vector3 v_normal[3];
};

int main() {
    try {
        framebuffer fb(1024, 1024);
        fb.clear({1, 0, 0, 1.0});
        renderer r(fb);

        camera cam;
        cam.pos.z = 3;

        cubemap skybox;
        skybox.load("assets/textures/skybox");

        model head("assets/models/african_head.obj");
        object_shader os(cam, fb.aspect(), skybox.sampler);
        os.bind_model(head);
        r.render(head.num_vertices(), os);

        fb.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
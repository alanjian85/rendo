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

    }

    virtual vector4 vert(int n) override {
        auto pos = vector4(model_->get_vertex(n), 1);
        v_pos[n % 3] = vector3(pos);
        v_normal[n % 3] = model_->get_normal(n);
        return camera_.proj(aspect_) * camera_.view() * pos;
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

    vector3 v_pos[3];
    vector3 v_normal[3];
};

class skybox_shader : public basic_shader {
public:
    skybox_shader(const camera& cam, double aspect, const sampler_cube& sampler_cube, const model& m) 
        : camera_(cam),
          aspect_(aspect),
          sampler_(sampler_cube),
          model_(m)
    {

    }

    virtual vector4 vert(int n) override {
        auto pos = model_.get_vertex(n + 6);
        v_pos[n % 3] = pos;
        return camera_.proj(aspect_) * camera_.view() * vector4(pos, 1);
    }

    virtual std::optional<color_rgba> frag(vector3 bar) override {
        auto pos = frag_lerp(v_pos, bar);
        //return sampler_(pos);
        return color_rgba(pos.x / 2 + 0.5, pos.y / 2 + 0.5, pos.z / 2 + 0.5, 1);
    }
private:
    double aspect_;
    const camera& camera_;
    const sampler_cube& sampler_;
    const model& model_;

    vector3 v_pos[3];
};

int main() {
    try {
        renderer r;
        r.clear({0.90, 0.88, 0.84, 1.0});
        //r.set_face_culling(cull_type::back);

        camera cam;
        cam.fov = 90;
        cam.pos.z = 1;
        cam.yaw = -110;
        cam.pitch = 20;

        cubemap skybox;
        skybox.load("assets/textures/skybox");

        model cube("assets/models/cube.obj");
        skybox_shader ss(cam, r.aspect(), skybox.sampler, cube);
        //r.disable_depth_writing();
        r.render(3, ss);

        model head("assets/models/african_head.obj");
        object_shader os(cam, r.aspect(), skybox.sampler);
        os.bind_model(head);
        r.enable_depth_writing();
        //r.render(head.num_vertices(), os);

        r.write("image.pam");
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
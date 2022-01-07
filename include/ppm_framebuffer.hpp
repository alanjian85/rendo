#ifndef RAYSTER_PPM_FRAMEBUFFER_HPP
#define RAYSTER_PPM_FRAMEBUFFER_HPP

#include "framebuffer.hpp"

namespace rayster {
    class ppm_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;

        virtual void write(const std::string& path) const override;
    };
}

#endif
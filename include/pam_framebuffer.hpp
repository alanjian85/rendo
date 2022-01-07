#ifndef RAYSTER_PAM_FRAMEBUFFER_HPP
#define RAYSTER_PAM_FRAMEBUFFER_HPP

#include "framebuffer.hpp"

namespace rayster {
    class pam_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;
    
        virtual void write(const std::string& path) const override;
    };
}

#endif
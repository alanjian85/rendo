#ifndef RAYSTER_PAM_FRAMEBUFFER_HPP
#define RAYSTER_PAM_FRAMEBUFFER_HPP

#include <iostream>

#include "framebuffer.hpp"

namespace rayster {
    class pam_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;
    };

    std::ostream& operator<<(std::ostream& lhs, const pam_framebuffer& rhs) noexcept;
}

#endif
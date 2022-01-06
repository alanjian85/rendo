#ifndef RAYSTER_PPM_FRAMEBUFFER_HPP
#define RAYSTER_PPM_FRAMEBUFFER_HPP

#include <iostream>

#include "framebuffer.hpp"

namespace rayster {
    class ppm_framebuffer : public framebuffer {
    public:
        using framebuffer::framebuffer;
    };

    std::ostream& operator<<(std::ostream& lhs, const ppm_framebuffer& rhs) noexcept;
}

#endif
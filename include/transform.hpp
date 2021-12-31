#ifndef RAYSTER_TRANSFORM_HPP
#define RAYSTER_TRANSFORM_HPP

#include <cstdlib>

#include "position3.hpp"
#include "vector3.hpp"

namespace rayster {
    class transform {
    public:
        using size_type = std::size_t;
    
        transform() = default;
        transform(double e00, double e01, double e02, double e03,
                  double e10, double e11, double e12, double e13,
                  double e20, double e21, double e22, double e23)
        {
            entries_[0][0] = e00; entries_[0][1] = e10; entries_[0][2] = e20;
            entries_[1][0] = e01; entries_[1][1] = e11; entries_[1][2] = e21;
            entries_[2][0] = e02; entries_[2][1] = e12; entries_[2][2] = e22;
            entries_[3][0] = e03; entries_[3][1] = e13; entries_[3][2] = e23;
        }

        double& operator()(size_type i, size_type j) noexcept {
            return entries_[j][i];
        }

        const double& operator()(size_type i, size_type j) const noexcept {
            return entries_[j][i];
        }
    private:
        double entries_[4][3];
    };

    vector3 operator*(const transform& lhs, vector3 rhs) noexcept;
    position3 operator*(const transform& lhs, position3 rhs) noexcept;
}

#endif
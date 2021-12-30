#include "vector2.hpp"
using namespace rayster;

#include <limits>

vector2 vector2::min() noexcept {
    return {
        std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min()
    };
}

vector2 vector2::max() noexcept {
    return {
        std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max()
    };
}
#ifndef RAYSTER_IVECTOR2_HPP
#define RAYSTER_IVECTOR2_HPP

#include <cstdlib>
#include <cmath>
#include <limits>

namespace rayster {
    struct ivector2 { 
        inline static ivector2 max() {
            return {
                std::numeric_limits<int>::max(),
                std::numeric_limits<int>::max()
            };
        }

        inline static ivector2 min() {
            return {
                std::numeric_limits<int>::min(),
                std::numeric_limits<int>::min()
            };
        }
        
        ivector2() 
            : x(), y() 
        {
        
        }
        
        ivector2(int x_, int y_) 
            : x(x_), y(y_)
        {
            
        }

        int& operator[](std::size_t index) noexcept {
            return index == 0 ? x : y;
        }

        const int& operator[](std::size_t index) const noexcept {
            return index == 0 ? x : y; 
        }

        int x;
        int y;
    };
}

#endif

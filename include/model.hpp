#ifndef RAYSTER_MODEL_HPP
#define RAYSTER_MODEL_HPP

#include <string>
#include <vector>

#include "vertex.hpp"

namespace rayster {
    class model {
    public:
        using size_type = std::vector<vertex>::size_type;
    
        void load(const std::string& path);
    private:
        std::vector<vertex> vertices_;
        std::vector<size_Type> indices_;
    };
}

#endif
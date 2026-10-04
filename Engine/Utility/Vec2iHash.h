#ifndef VEC2IHASH_H
#define VEC2IHASH_H

#include <cstdint>
#include "../Mxm/Vec2i.h"

struct Vec2iHash final
{
    uint32_t operator()(const Mxm::Vec2i& vec) const noexcept {
        uint32_t a = static_cast<uint32_t>(vec.x);
        uint32_t b = static_cast<uint32_t>(vec.y);

        a = a * 91814547 ^ b * 3875478349;
        a ^= (b << 2) * 85472143;
        a ^= (a >> 16) ^ (b >> 8);
        
        return a;
    }
};

#endif

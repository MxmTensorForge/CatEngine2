#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>

namespace MathUtils
{
    inline int fastFloorDiv(int a, int b) noexcept {
        int r = a / b;
        if (a % b < 0) r--;
        return r;
    }
    
    template<typename T>
    inline const T& min(const T& a, const T& b) noexcept {
        return a < b ? a : b;
    }
    template<typename T>
    inline const T& max(const T& a, const T& b) noexcept {
        return a > b ? a : b;
    }
    
    template<typename T>
    inline T clamp(const T& x, const T& low, const T& high) noexcept {
        return min(max(x, low), high);
    }

    inline float hash(int a, int b, unsigned int seed) noexcept {
        unsigned int h = static_cast<unsigned int>(a * 73856093) ^ 
                         static_cast<unsigned int>(b * 19349663) ^
                         static_cast<unsigned int>(seed * 828716474);
        h = h * 0x9e3779b9;
        h = h ^ (h >> 16);
        return h / 4294967295.0f;
    }
    inline float lerp(float a, float b, float t) noexcept {
        return a + (b - a) * t;
    }
    inline float smoothstep(float t) noexcept {
        return t * t * (3.0f - 2.0f * t);
    }
    inline float noise(float x, float y, unsigned int seed) noexcept {
        int xi = (int)floorf(x);
        int yi = (int)floorf(y);

        float fx = x - (float)xi;
        float fy = y - (float)yi;

        float hash00 = hash(xi, yi,         seed);
        float hash10 = hash(xi + 1, yi,     seed);
        float hash01 = hash(xi, yi + 1,     seed);
        float hash11 = hash(xi + 1, yi + 1, seed);

        float sx = smoothstep(fx);
        float sy = smoothstep(fy);

        return lerp(lerp(hash00, hash10, sx), lerp(hash01, hash11, sx), sy);
    }
}

#endif

#ifndef MINKOWSKITRIANGLE_H
#define MINKOWSKITRIANGLE_H

#include "MinkowskiPoint.h"

class MinkowskiTriangle
{
private:
    MinkowskiPoint _vertices[3];
    Mxm::Vec3 _normal{};
public:
    MinkowskiTriangle() = default;
    ~MinkowskiTriangle() = default;

    MinkowskiTriangle(const MinkowskiPoint& vert0, const MinkowskiPoint& vert1, const MinkowskiPoint& vert2) : _vertices{ vert0, vert1, vert2 } { calcNormal(); }

    const MinkowskiPoint& operator[](size_t i) const noexcept { return _vertices[i]; }
    MinkowskiPoint& operator[](size_t i) noexcept { return _vertices[i]; }

    void calcNormal() noexcept {
        Mxm::Vec3 edge1 = _vertices[1].point - _vertices[0].point;
        Mxm::Vec3 edge2 = _vertices[2].point - _vertices[0].point;
        _normal = edge1.cross(edge2).normalized();
    }
    const Mxm::Vec3& normal() const noexcept { return _normal; }

    Mxm::Vec3 getProjBaryCoords(const Mxm::Vec3& point) const noexcept {
        const Mxm::Vec3& a = _vertices[0];
        const Mxm::Vec3& b = _vertices[1];
        const Mxm::Vec3& c = _vertices[2];
    
        Mxm::Vec3 v0 = b - a;
        Mxm::Vec3 v1 = c - a;
        Mxm::Vec3 v2 = point - a;
    
        float d00 = v0.dot(v0);
        float d01 = v0.dot(v1);
        float d11 = v1.dot(v1);
        float d20 = v2.dot(v0);
        float d21 = v2.dot(v1);
    
        float denom = d00 * d11 - d01 * d01;
    
        if (fabsf(denom) < Mxm::Consts::EPS) {
            return Mxm::Vec3(1.0f, 0.0f, 0.0f);
        }
    
        float v = (d11 * d20 - d01 * d21) / denom;
        float w = (d00 * d21 - d01 * d20) / denom;
        
        float u = 1.0f - v - w;
    
        return Mxm::Vec3(u, v, w);
    }
};

#endif

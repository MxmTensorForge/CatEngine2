#ifndef CAPSULESHAPE_H
#define CAPSULESHAPE_H

#include "ColliderShape.h"

#include <vector>

class CapsuleShape final : public ColliderShape
{
private:
    Mxm::Vec3 _a;
    Mxm::Vec3 _b;
    float _radius;
public:
    CapsuleShape(const Mxm::Vec3& a, const Mxm::Vec3& b, float r) : _a{ a }, _b{ b }, _radius { r } {}

    Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept override {
        float dotA = direction.dot(_a);
        float dotB = direction.dot(_b);

        Mxm::Vec3 point = dotA >= dotB ? _a : _b;
        return point + direction.normalized() * _radius;
    }
};

#endif // !CAPSULESHAPE_H

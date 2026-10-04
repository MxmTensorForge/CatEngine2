#ifndef SPHERESHAPE_H
#define SPHERESHAPE_H

#include "ColliderShape.h"

#include <vector>

class SphereShape final : public ColliderShape
{
private:
    Mxm::Vec3 _center;
    float _radius;
public:
    SphereShape(const Mxm::Vec3& c, float r) : _center{ c }, _radius{ r } {}

    Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept override {
        return _center + direction.normalized() * _radius;
    }
};

#endif // !SPHERESHAPE_H

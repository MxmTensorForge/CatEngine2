#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "ColliderShape.h"

#include <vector>

class BoxShape final : public ColliderShape
{
private:
    Mxm::Vec3 _center;
    Mxm::Vec3 _extent;
public:
    BoxShape(const Mxm::Vec3& c, const Mxm::Vec3& e) : _center{c}, _extent{e} {}

    Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept override {
        return Mxm::Vec3(
            _center.x + (direction.x >= 0 ? _extent.x : -_extent.x),
            _center.y + (direction.y >= 0 ? _extent.y : -_extent.y),
            _center.z + (direction.z >= 0 ? _extent.z : -_extent.z)
        );
    }
};

#endif // !BOXSHAPE_H

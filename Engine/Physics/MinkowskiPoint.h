#ifndef MINKOWSKIPOINT_H
#define MINKOWSKIPOINT_H

#include "../Mxm/Vec3.h"

struct MinkowskiPoint
{
    Mxm::Vec3 point;
    Mxm::Vec3 a, b;

    operator Mxm::Vec3() const noexcept { return point; }
    const Mxm::Vec3& toVec3() const noexcept { return point; }
};

#endif

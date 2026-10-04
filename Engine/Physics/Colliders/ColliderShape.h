#ifndef COLLIDERSHAPE_H
#define COLLIDERSHAPE_H

#include "../../Mxm/Vec3.h"

class ColliderShape
{
public:
	virtual ~ColliderShape() = default;
	virtual Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept = 0;
};

#endif // !COLLIDERSHAPE_H

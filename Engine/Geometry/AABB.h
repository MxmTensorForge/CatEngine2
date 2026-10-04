#ifndef AABB_H
#define AABB_H

#include "../Mxm/Vec3.h"

struct AABB
{
	Mxm::Vec3 center;
	Mxm::Vec3 extent;

	bool isIntersection(const Mxm::Vec3& ro, const Mxm::Vec3& rd) const noexcept;
};

#endif // !AABB_H

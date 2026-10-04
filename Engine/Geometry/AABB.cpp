#include "AABB.h"
#include <utility>

bool AABB::isIntersection(const Mxm::Vec3& ro, const Mxm::Vec3& rd) const noexcept {
	Mxm::Vec3 max = center + extent;
	Mxm::Vec3 min = center - extent;

	if (rd.dot(rd) < 0.0001f) return false;
	Mxm::Vec3 tMin = Mxm::Vec3((min - ro) / rd);
	Mxm::Vec3 tMax = Mxm::Vec3((max - ro) / rd);

	if (rd.x < 0.0f) std::swap(tMin.x, tMax.x);
	if (rd.y < 0.0f) std::swap(tMin.y, tMax.y);
	if (rd.z < 0.0f) std::swap(tMin.z, tMax.z);

	float tNear = std::max(std::max(tMin.x, tMin.y), tMin.z);
	float tFar = std::min(std::min(tMax.x, tMax.y), tMax.z);

	return (tNear <= tFar) && (tFar >= 0.0f);
}

// minX <= O + tD <= maxX
// minX - O <= tD <= maxX - O
// (minX - O) / D <= t <= (maxX - O) / D
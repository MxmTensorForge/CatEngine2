#include "Plane.h"

#include "../Mxm/Consts.h"

float Plane::distance(const Mxm::Vec3& point) const noexcept {
	return _normal.dot(point - _point);
}

Mxm::Vec4 Plane::intersection(const Mxm::Vec4& from, const Mxm::Vec4& to) const noexcept {
	float d1 = distance(from.toVec3());
	float d2 = distance(to.toVec3());

	float denom = d1 - d2;
	if (denom < Mxm::Consts::EPS) return from;

	float t = d1 / denom;
	return from + (to - from) * t;
}

void Plane::clip(const Triangle& polygon, std::vector<Triangle>& outResult, std::vector<Mxm::Vec4>& insidePoints, std::vector<Mxm::Vec4>& outsidePoints) const noexcept
{
	insidePoints.clear();
	outsidePoints.clear();

	float distances[3] = {
		distance(polygon[0].toVec3()),
		distance(polygon[1].toVec3()),
		distance(polygon[2].toVec3())
	};

	for (int i = 0; i < 3; i++)
	{
		if (distances[i] >= 0) {
			insidePoints.emplace_back(polygon[i]);
		}
		else {
			outsidePoints.emplace_back(polygon[i]);
		}
	}

	if (insidePoints.size() == 1) {
		Mxm::Vec4 intersect1 = intersection(insidePoints[0], outsidePoints[0]);
		Mxm::Vec4 intersect2 = intersection(insidePoints[0], outsidePoints[1]);

		outResult.emplace_back(insidePoints[0], intersect1, intersect2, polygon.color());
	}
	if (insidePoints.size() == 2) {
		Mxm::Vec4 intersect1 = intersection(insidePoints[0], outsidePoints[0]);
		Mxm::Vec4 intersect2 = intersection(insidePoints[1], outsidePoints[0]);

		outResult.emplace_back(insidePoints[0], intersect1, intersect2, polygon.color());
		outResult.emplace_back(insidePoints[0], intersect2, insidePoints[1], polygon.color());
	}
	if (insidePoints.size() == 3) {
		outResult.emplace_back(polygon);
	}
}
#ifndef PLANE_H
#define PLANE_H

#include "../Mxm/Vec3.h"
#include <vector>
#include "Triangle.h"

class Plane
{
private:
	Mxm::Vec3 _normal{};
	Mxm::Vec3 _point{};
public:
	Plane(const Mxm::Vec3& vec, const Mxm::Vec3& point) : _normal(vec), _point(point) {};
	~Plane() = default;

	float distance(const Mxm::Vec3& point) const noexcept;
	Mxm::Vec4 intersection(const Mxm::Vec4& from, const Mxm::Vec4& to) const noexcept;

	void clip(const Triangle& polygon, std::vector<Triangle>& outResult, std::vector<Mxm::Vec4>& insidePoints, std::vector<Mxm::Vec4>& outsidePoints) const noexcept;
};

#endif
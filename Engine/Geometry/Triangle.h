#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Mxm/Mat4.h"

class Triangle
{
private:
	Mxm::Vec3 _vertices[3];
	Mxm::Vec3 _normal{};
public:
	Triangle() = default;
	~Triangle() = default;

	Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2);

	const Mxm::Vec3& operator[](size_t i) const noexcept;
	Mxm::Vec3& operator[](size_t i) noexcept;

	void calcNormal() noexcept;
	const Mxm::Vec3& normal() const noexcept;

	bool intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, Mxm::Vec3& outPoint, float& d) const noexcept;

	void applyMatrix(const Mxm::Mat4& mat, bool recalculateNormal = true) noexcept;
	Triangle operator*(const Mxm::Mat4& matrix) const noexcept;

	Mxm::Vec3 getProjBaryCoords(const Mxm::Vec3& point) const noexcept;
};

#endif

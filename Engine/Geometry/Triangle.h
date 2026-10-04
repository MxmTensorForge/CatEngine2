#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Mxm/Mat4.h"
#include "../Graphics/Color.h"

class Triangle
{
private:
	Mxm::Vec4 _vertices[3];
	Color _color{};

	Mxm::Vec3 _normal{};

	void calcNormal() noexcept;
public:
	Triangle() = default;
	~Triangle() = default;

	Triangle(const Mxm::Vec4& vert0, const Mxm::Vec4& vert1, const Mxm::Vec4& vert2);
	Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2);
	Triangle(const Mxm::Vec4& vert0, const Mxm::Vec4& vert1, const Mxm::Vec4& vert2, Color col);
	Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2, Color col);

	const Mxm::Vec4& operator[](size_t i) const noexcept;

	const Color color() const noexcept;
	const Mxm::Vec3& normal() const noexcept;

	bool intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, Mxm::Vec3& outPoint, float& d) const noexcept;

	void applyMatrix(const Mxm::Mat4& mat, bool recalculateNormal = true) noexcept;
	Triangle operator*(const Mxm::Mat4& matrix) const noexcept;
};

#endif
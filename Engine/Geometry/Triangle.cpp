#include "Triangle.h"

#include "../Mxm/Mat3.h"

Triangle::Triangle(const Mxm::Vec4& vert0, const Mxm::Vec4& vert1, const Mxm::Vec4& vert2) : _vertices{ vert0, vert1, vert2 } {
	calcNormal();
}
Triangle::Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2) : _vertices{ Mxm::Vec4(vert0, 1.0f), Mxm::Vec4(vert1, 1.0f), Mxm::Vec4(vert2, 1.0f) } {
	calcNormal();
}
Triangle::Triangle(const Mxm::Vec4& vert0, const Mxm::Vec4& vert1, const Mxm::Vec4& vert2, Color col) : _vertices{ vert0, vert1, vert2 }, _color(col) {
	calcNormal();
}
Triangle::Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2, Color col) : _vertices{ Mxm::Vec4(vert0, 1.0f), Mxm::Vec4(vert1, 1.0f), Mxm::Vec4(vert2, 1.0f) }, _color(col) {
	calcNormal();
}

void Triangle::calcNormal() noexcept {
	Mxm::Vec3 edge1 = (_vertices[1] - _vertices[0]).toVec3();
	Mxm::Vec3 edge2 = (_vertices[2] - _vertices[0]).toVec3();

	_normal = edge1.cross(edge2).normalized();
}

const Mxm::Vec4& Triangle::operator[](size_t i) const noexcept {
	return _vertices[i];
}

const Color Triangle::color() const noexcept {
	return _color;
}
const Mxm::Vec3& Triangle::normal() const noexcept {
	return _normal;
}

bool Triangle::intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, Mxm::Vec3& outPoint, float& d) const noexcept {
	Mxm::Vec3 edge1 = (_vertices[1] - _vertices[0]).toVec3();
	Mxm::Vec3 edge2 = (_vertices[2] - _vertices[0]).toVec3();

	Mxm::Vec3 to = origin - (_vertices[0]).toVec3();

	Mxm::Mat3 mat = Mxm::Mat3(
		edge1.x, edge2.x, -dir.x,
		edge1.y, edge2.y, -dir.y,
		edge1.z, edge2.z, -dir.z
	);
	Mxm::Vec3 result = mat.inversed() * to;

	if (result.x >= -Mxm::Consts::EPS && result.y >= -Mxm::Consts::EPS && 1.0f - result.x - result.y >= -Mxm::Consts::EPS) {
		if (result.z < 0.0f) return false;

		outPoint = origin + dir * result.z;
		d = result.z;
		return true;
	}
	return false;
}

void Triangle::applyMatrix(const Mxm::Mat4& mat, bool recalculateNormal) noexcept {
	for (auto& v : _vertices) {
		v = mat * v;
	}
	if (recalculateNormal) calcNormal();
}
Triangle Triangle::operator*(const Mxm::Mat4& matrix) const noexcept {
	return Triangle(matrix * _vertices[0], matrix * _vertices[1], matrix * _vertices[2], _color);
}
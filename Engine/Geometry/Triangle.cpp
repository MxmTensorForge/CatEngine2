#include "Triangle.h"

#include "../Mxm/Mat3.h"

Triangle::Triangle(const Mxm::Vec3& vert0, const Mxm::Vec3& vert1, const Mxm::Vec3& vert2) : _vertices{ vert0, vert1, vert2 } {
	calcNormal();
}

const Mxm::Vec3& Triangle::operator[](size_t i) const noexcept {
	return _vertices[i];
}

void Triangle::calcNormal() noexcept {
	Mxm::Vec3 edge1 = _vertices[1] - _vertices[0];
	Mxm::Vec3 edge2 = _vertices[2] - _vertices[0];

	_normal = edge1.cross(edge2).normalized();
}
const Mxm::Vec3& Triangle::normal() const noexcept {
	return _normal;
}

bool Triangle::intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, Mxm::Vec3& outPoint, float& d) const noexcept {
	Mxm::Vec3 edge1 = _vertices[1] - _vertices[0];
	Mxm::Vec3 edge2 = _vertices[2] - _vertices[0];

	Mxm::Vec3 to = origin - _vertices[0];

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
		v = (mat * Mxm::Vec4(v, 1.0f)).toVec3();
	}
	if (recalculateNormal) calcNormal();
}
Triangle Triangle::operator*(const Mxm::Mat4& matrix) const noexcept {
    Triangle tri = *this;
    tri.applyMatrix(matrix, true);
    
	return tri;
}

Mxm::Vec3 Triangle::getProjBaryCoords(const Mxm::Vec3& point) const noexcept {
    const Mxm::Vec3& a = _vertices[0];
    const Mxm::Vec3& b = _vertices[1];
    const Mxm::Vec3& c = _vertices[2];

    Mxm::Vec3 v0 = b - a;
    Mxm::Vec3 v1 = c - a;
    Mxm::Vec3 v2 = point - a;

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);

    float denom = d00 * d11 - d01 * d01;

    if (fabsf(denom) < Mxm::Consts::EPS) {
        return Mxm::Vec3(1.0f, 0.0f, 0.0f);
    }

    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    
    float u = 1.0f - v - w;

    return Mxm::Vec3(u, v, w);
}

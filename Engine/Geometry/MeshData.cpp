#include "MeshData.h"

void MeshData::calculateNormals() noexcept {
	normals.resize(indices.size() / 3);
	for (int i = 0; i < indices.size(); i += 3)
	{
		const Mxm::Vec3& v0 = vertices[indices[i]];
		const Mxm::Vec3& v1 = vertices[indices[i + 1]];
		const Mxm::Vec3& v2 = vertices[indices[i + 2]];

		Mxm::Vec3 edge0 = v1 - v0;
		Mxm::Vec3 edge1 = v2 - v0;

		Mxm::Vec3 faceNormal = edge0.cross(edge1);
		normals[i / 3] = faceNormal.normalized();;
	}
}
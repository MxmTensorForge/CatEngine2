#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>
#include "../Mxm/Vec3.h"
#include "../Graphics/Color.h"
#include "../Graphics/GPUData.h"

struct MeshData {
	std::vector<Mxm::Vec3> vertices;
	std::vector<unsigned int> indices;

	std::vector<Mxm::Vec3> normals;

	std::vector<Mxm::Vec2> textureCoords;
	std::vector<unsigned int> textureIndices;

	GPUData data;

	void calculateNormals() noexcept;
};

#endif // !MESH_H

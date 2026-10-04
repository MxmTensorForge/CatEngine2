#ifndef GPUDATA_H
#define GPUDATA_H

#include "VertexArray.h"
#include "Buffer.h"

#include <memory>
#include <vector>

#include "Color.h"
#include "../Mxm/Vec3.h"

class Color;

class GPUData
{
private:
	std::unique_ptr<VertexArray> _vao;
	std::unique_ptr<Buffer> _vbo;

	size_t _verticesCount = 0;
public:
	GPUData();
	~GPUData();

	GPUData(const GPUData&) = delete;
	GPUData& operator=(const GPUData&) = delete;

	GPUData(GPUData&&) noexcept = default;
	GPUData& operator=(GPUData&&) noexcept = default;

	void loadData(const std::vector<Mxm::Vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<Mxm::Vec3>& normals,
		const std::vector<Mxm::Vec2>& texCoords, const std::vector<unsigned int>& textureIndices);
	void draw() const noexcept;
};

#endif // !GPUDATA_H
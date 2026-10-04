#include "GPUData.h"

GPUData::GPUData() {
	_vao = std::make_unique<VertexArray>();
	_vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER);
}
GPUData::~GPUData() {

}

void GPUData::loadData(const std::vector<Mxm::Vec3>& vertices, const std::vector<unsigned int>& indices, const std::vector<Mxm::Vec3>& normals,
	const std::vector<Mxm::Vec2>& texCoords, const std::vector<unsigned int>& textureIndices) {
	
	std::vector<float> vertexData;
	
	vertexData.reserve(indices.size());
	_verticesCount = indices.size();

	for (size_t i = 0; i < indices.size(); i++) {
		vertexData.push_back(vertices[indices[i]].x);
		vertexData.push_back(vertices[indices[i]].y);
		vertexData.push_back(vertices[indices[i]].z);

		vertexData.push_back(normals[i / 3].x);
		vertexData.push_back(normals[i / 3].y);
		vertexData.push_back(normals[i / 3].z);

		if (texCoords.size() > 0) {
			vertexData.push_back(texCoords[textureIndices[i]].x);
			vertexData.push_back(texCoords[textureIndices[i]].y);
		}
		else
		{
			vertexData.push_back(0.0f);
			vertexData.push_back(0.0f);
		}
	}

	_vao->bind();
	_vbo->bind();
	_vbo->bufferData(vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	_vao->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	_vao->enableAttribute(0);
	_vao->setAttribute(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	_vao->enableAttribute(1);
	_vao->setAttribute(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	_vao->enableAttribute(2);

	_vbo->unBind();
	_vao->unBind();
}
void GPUData::draw() const noexcept {
	_vao->bind();
	_vbo->bind();
	glDrawArrays(GL_TRIANGLES, 0, _verticesCount);
}

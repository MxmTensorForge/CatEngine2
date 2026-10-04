#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <memory>

#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

#include "../Mxm/Mat4.h"
#include "GPUData.h"

#include <vector>

class Camera;
class Material;

class PointLight;
class DirectionLight;

class SkyBox;

class MeshRenderer final
{
private:
	std::unique_ptr<Shader> _shader;
	std::unique_ptr<Shader> _skyboxShader;

	std::unique_ptr<VertexArray> _skyboxVAO;
	std::unique_ptr<Buffer> _skyboxVBO;
public:
	MeshRenderer();
	~MeshRenderer();

	void init();
	void update(const Camera* camera, 
		const std::vector<PointLight*>& pointLights, const DirectionLight* directionLight);

	void clear(Color color) const noexcept;
	void viewport(GLsizei width, GLsizei height) const noexcept;

	void setDrawFrame(bool state) const noexcept;
	void setAmbientColor(Color color) const noexcept;

	void drawMesh(const Mxm::Mat4& model, const Material* material);
	void drawSkyBox(const SkyBox* skybox);
};

#endif // !RENDERER_H

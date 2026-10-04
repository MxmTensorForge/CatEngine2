#include "MeshRenderer.h"

#include "../ComponentSystem/Components/MeshComponent.h"
#include "../ComponentSystem/Components/Material.h"
#include "../ComponentSystem/Components/SkyBox.h"
#include "../ComponentSystem/Components/Camera.h"

#include "../ComponentSystem/Components/PointLight.h"
#include "../ComponentSystem/Components/DirectionLight.h"

#include "../ComponentSystem/Object/GameObject.h"

#include "../Managers/TextureManager.h"

#include "../Core/Logger.h"
#include "../Core/EngineConsts.h"

#include "Texture.h"
#include "CubeMap.h"
#include "Cube.h"

MeshRenderer::MeshRenderer() : _shader(nullptr) {}
MeshRenderer::~MeshRenderer() {}

void MeshRenderer::init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnable(GL_MULTISAMPLE);

	_shader = std::make_unique<Shader>(EngineConsts::VERTEX_SHADER_PATH, EngineConsts::FRAGMENT_SHADER_PATH);
	_skyboxShader = std::make_unique<Shader>(EngineConsts::VERTEX_SKYBOX_SHADER_PATH, EngineConsts::FRAGMENT_SKYBOX_SHADER_PATH);

	_skyboxVAO = std::make_unique<VertexArray>();
	_skyboxVBO = std::make_unique<Buffer>(GL_ARRAY_BUFFER);

	_skyboxVAO->bind();
	_skyboxVBO->bind();

	_skyboxVBO->bufferData(sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);
	_skyboxVAO->setAttribute(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	_skyboxVAO->enableAttribute(0);

	Logger::getInstance().log(LogType::Message, "Renderer has been successfully initialized");
}
void MeshRenderer::update(const Camera* camera,
	const std::vector<PointLight*>& pointLights, const DirectionLight* directionLight) {

	_shader->use();
	_shader->setUniform("uProjection", camera->getProjectionMatrix().data(), true);
	_shader->setUniform("uView", camera->getViewMatrix().data(), true);

	Mxm::Vec3 camPos = camera->getObject()->transform().getWorldPosition();
	_shader->setUniform("uCameraPos", camPos.x, camPos.y, camPos.z);

	int lightCount = pointLights.size();
	_shader->setUniform("pointLightsCount", lightCount);
	for (int i = 0; i < lightCount; i++) {
		if (i > 8) break;

		auto light = pointLights[i];
		if (!light || !light->getObject()->getActive()) continue;

		std::string name = "pointLights[" + std::to_string(i) + "].";
		_shader->setUniform(name + "linearFading", light->getLinearFading());
		_shader->setUniform(name + "quadraticFading", light->getQuadraticFading());
		_shader->setUniform(name + "intensity", light->getIntensity());

		Color color = light->getLightColor();
		_shader->setUniform(name + "lightColor", color.rf(), color.gf(), color.bf());

		Mxm::Vec3 pos = light->getObject()->transform().getWorldPosition();
		_shader->setUniform(name + "lightPos", pos.x, pos.y, pos.z);
	}

	if (directionLight && directionLight->getObject()->getActive()) {
		std::string name = "directionLight.";
		_shader->setUniform(name + "intensity", directionLight->getIntensity());

		Color color = directionLight->getLightColor();
		_shader->setUniform(name + "lightColor", color.rf(), color.gf(), color.bf());

		Mxm::Vec3 dir = directionLight->getObject()->transform().getForward();
		_shader->setUniform(name + "direction", dir.x, dir.y, dir.z);
	}

	_skyboxShader->use();
	_skyboxShader->setUniform("uProjection", camera->getProjectionMatrix().data(), true);

	const Transform& cameraTransform = camera->getObject()->transform();
	
	Mxm::Mat4 view = Mxm::Mat4::view(cameraTransform.getRight(), cameraTransform.getUp(), cameraTransform.getForward(), Mxm::Vec3(0.0f));
	_skyboxShader->setUniform("uView", view.data(), true);
}

void MeshRenderer::clear(Color color) const noexcept {
	glClearColor(color.rf(), color.gf(), color.bf(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void MeshRenderer::viewport(GLsizei width, GLsizei height) const noexcept {
	glViewport(0, 0, width, height);
}
void MeshRenderer::setDrawFrame(bool state) const noexcept {
	glPolygonMode(GL_FRONT_AND_BACK, state ? GL_LINE : GL_FILL);
}
void MeshRenderer::setAmbientColor(Color color) const noexcept {
    _shader->use();
	_shader->setUniform("uAmbient", color.rf(), color.gf(), color.bf());
}

void MeshRenderer::drawMesh(const Mxm::Mat4& model, const Material* material) {
	auto* mesh = material->getObject()->getComponent<MeshComponent>();
	if (!mesh) return;

	_shader->use();
	_shader->setUniform("uModel", model.data(), true);

	Color color = material->getColor();
	_shader->setUniform("uColor", color.rf(), color.gf(), color.bf(), color.af());
	_shader->setUniform("uShininess", material->getShininess());
	_shader->setUniform("uSpecular", material->getSpecular());
	_shader->setUniform("uUvScale", material->getUvScale());

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	if (color.a() < 255) {
		glDepthMask(GL_FALSE);
	}

	std::string texName = material->getTextureName();
	if (texName.empty()) {
		_shader->setUniform("uUseTexture", 0);
	}
	else {
		TextureManager::getInstance().getTexture(texName)->bind(GL_TEXTURE0);
		_shader->setUniform("uUseTexture", 1);
		_shader->setUniform("uTexture", 0);
	}
	_shader->setUniform("uIsShaded", material->isShaded() ? 1 : 0);

	if (material->isTwoSided()) glDisable(GL_CULL_FACE);
	else glEnable(GL_CULL_FACE);

	mesh->getData()->data.draw();
	
	glDepthMask(GL_TRUE);
	glDisable(GL_POLYGON_OFFSET_FILL);
}

void MeshRenderer::drawSkyBox(const SkyBox* skybox) {
    _skyboxShader->use();
    _skyboxVAO->bind();

    glDisable(GL_CULL_FACE);

    TextureManager::getInstance().getCubeMap(skybox->getCubeMapName())->bind(GL_TEXTURE0);
    _skyboxShader->setUniform("uSkyBox", 0);

    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

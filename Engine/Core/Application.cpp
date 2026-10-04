#include "Application.h"

#include "../ComponentSystem/Object/Transform.h"
#include "../ComponentSystem/Components/Camera.h"
#include "../ComponentSystem/Components/Material.h"
#include "../ComponentSystem/Components/SkyBox.h"
#include "../Animation/Animator.h"

#include "../Managers/SceneManager.h"

#include "../UI/UISystem.h"

#include "../Graphics/DebugRenderer.h"

#include "Logger.h"
#include "Time.h"
#include "EngineConsts.h"

#include "Input.h"

#include "../Utility/MathUtils.h"

#include <algorithm>

void Application::initialize() {
	_screen = std::make_unique<Screen>();
	_meshRenderer = std::make_unique<MeshRenderer>();
	_uiRenderer = std::make_unique<UIRenderer>();

	Logger::getInstance().setLogFile("log.txt");

	if (!_screen->open(_width, _height)) return;
	auto& sceneManager = SceneManager::getInstance();

	_meshRenderer->init();
	_meshRenderer->viewport(_width, _height);
	_uiRenderer->init(_width, _height);

	DebugRenderer::getInstance().init();

	start();
	sceneManager.processPendingScene();
}
void Application::updatePhysics() {
	Time::begin("updatePhysics");

	auto& sceneManager = SceneManager::getInstance();
	auto activeScene = sceneManager.getActiveScene();

	Time::_accumulator += Time::deltaTime();
	
	while (Time::_accumulator >= Time::fixedDeltaTime()) {
		activeScene->fixedUpdate();
		fixedUpdate();

		activeScene->updateCollisions();

		Time::_accumulator -= Time::fixedDeltaTime();
	}

	Time::_physicsAlpha = MathUtils::clamp(Time::_accumulator / Time::fixedDeltaTime(), 0.0f, 1.0f);

	Time::end("updatePhysics");
}
void Application::updateGame() {
	Time::begin("updateGame");

	auto& sceneManager = SceneManager::getInstance();
	auto activeScene = sceneManager.getActiveScene();

	activeScene->interpolatePhysics();

	update();
	activeScene->updateAnimator();
	activeScene->update();

	Time::end("updateGame");
}

void Application::renderOpaque() {
	auto& sceneManager = SceneManager::getInstance();
	auto activeScene = sceneManager.getActiveScene();

	_transparentMaterials.clear();
	for (const auto& obj : activeScene->getGameObjects()) {
		if (!obj->getActive()) continue;

		auto material_ptr = obj->getComponent<Material>();
		if (!material_ptr) continue;

		if (material_ptr->getColor().a() < 255) {
			_transparentMaterials.push_back(material_ptr);
			continue;
		}

		auto& transform = obj->transform();

		_meshRenderer->drawMesh(transform.getWorldMatrix(), material_ptr);
	}

	for (const auto& obj : activeScene->getGameObjects()) {
		if (!obj->getActive()) continue;

		auto skybox_ptr = obj->getComponent<SkyBox>();
		if (!skybox_ptr) continue;

		_meshRenderer->drawSkyBox(skybox_ptr);
	}
}
void Application::renderTransparent(GameObject* camera) {
	const Mxm::Vec3& camPos = camera->transform().getWorldPosition();
	std::sort(_transparentMaterials.begin(), _transparentMaterials.end(), [&camPos](Material* mat1, Material* mat2) {
		Mxm::Vec3 pos1 = mat1->getObject()->transform().getWorldPosition();
		Mxm::Vec3 pos2 = mat2->getObject()->transform().getWorldPosition();

		float dist1 = (pos1 - camPos).length2();
		float dist2 = (pos2 - camPos).length2();

		return dist1 > dist2;
	});

	for (const auto& material : _transparentMaterials) {
		auto obj = material->getObject();
		if (!obj->getActive()) continue;

		auto& transform = obj->transform();
		_meshRenderer->drawMesh(transform.getWorldMatrix(), material);
	}
}
void Application::renderFrame() {
	Time::begin("renderFrame");

	auto& sceneManager = SceneManager::getInstance();
	auto activeScene = sceneManager.getActiveScene();

	auto* camera = activeScene->getMainCamera();
	if (!camera) return;
	auto* cameraComp = camera->getComponent<Camera>();
	
	_meshRenderer->update(cameraComp, activeScene->getPointLights(), activeScene->getDirectionLight());
	
	_meshRenderer->setAmbientColor(activeScene->getAmbientColor());
	_meshRenderer->clear(activeScene->getBackgroundColor());

	renderOpaque();
	renderTransparent(camera);
	DebugRenderer::getInstance().flush(cameraComp);

	Time::end("renderFrame");
}
void Application::renderUI() {
	Time::begin("renderUI");

	UISystem::getInstance().render(_uiRenderer.get());
	_uiRenderer->flush();

	Time::end("renderUI");
}

void Application::applySceneChanges() {
	auto& sceneManager = SceneManager::getInstance();

	if (sceneManager.hasPendingScene()) {
		sceneManager.processPendingScene();
	}
}

bool Application::processFrame() {
	Input::update();
	if (!_screen->pollEvents()) return false;

	UISystem::getInstance().newFrame();

	Time::update();

	updatePhysics();

	applySceneChanges();
	updateGame();
	applySceneChanges();

	renderFrame();
	renderUI();

	swapBuffers();

	return true;
}
void Application::swapBuffers() {
	_screen->swap();
}

void Application::run() {
	initialize();

	bool isRunning = true;
	while (isRunning)
	{
		isRunning = processFrame();

		_stateAccumulator += Time::deltaTime();
		if (_stateAccumulator >= 1.0f) {
			_stateAccumulator = 0.0f;

			float update = Time::get("updateGame");
			float physics = Time::get("updatePhysics");
			float renderFrame = Time::get("renderFrame");
			float renderUI = Time::get("renderUI");

			Logger::getInstance().log(LogType::Message, "<- All: " + std::to_string(update + physics + renderFrame + renderUI) + " ms");
			Logger::getInstance().log(LogType::Message, "<  Game update: " + std::to_string(update) + " ms");
			Logger::getInstance().log(LogType::Message, "<  Physics update: " + std::to_string(physics) + " ms");
			Logger::getInstance().log(LogType::Message, "<  Rendering frame: " + std::to_string(renderFrame) + " ms");
			Logger::getInstance().log(LogType::Message, "<  Rendering ui: " + std::to_string(renderUI) + " ms");
			Logger::getInstance().log(LogType::Message, "<  FPS: " + std::to_string(Time::fps()));
		}
	}
	shutdown();
	_screen->close();
}

void Application::setDrawFrame(bool state) noexcept {
	_meshRenderer->setDrawFrame(state);
}

Application::Application() : _width(EngineConsts::STANDART_WIDTH), _height(EngineConsts::STANDART_HEIGHT), _screen() {}

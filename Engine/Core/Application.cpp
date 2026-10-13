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

void Application::renderOpaqueTransparent(GameObject* camera) {
	auto& sceneManager = SceneManager::getInstance();
	auto activeScene = sceneManager.getActiveScene();

	struct OpaqueRenderItem final
	{
        const MeshComponent* meshComp = nullptr;
	    const Material* materialComp = nullptr;
		const Mxm::Mat4* worldMatrix = nullptr;
		uint64_t batchKey = 0ULL;
	};
	struct TransparentRenderItem final
	{
        const MeshComponent* meshComp = nullptr;
	    const Material* materialComp = nullptr;
		const Mxm::Mat4* worldMatrix = nullptr;
		uint64_t batchKey = 0ULL;
		float distance = 0.0f;
	};

	static std::vector<OpaqueRenderItem> opaqueQueue;
	static std::vector<TransparentRenderItem> transparentQueue;

	opaqueQueue.clear();
	transparentQueue.clear();

	Mxm::Vec3 cameraWorldPos = camera->transform().getWorldPosition();
	
	for (const auto& obj : activeScene->getGameObjects()) {
		if (!obj->getActive()) continue;

		auto mesh_ptr = obj->getComponent<MeshComponent>();
		if (!mesh_ptr) continue;

		auto material_ptr = obj->getComponent<Material>();
		if (!material_ptr) continue;

		uint64_t batchKey = (reinterpret_cast<uintptr_t>(mesh_ptr->getData()) ^ material_ptr->generateSignature()) * 0xbf58476d1ce4e5b9ULL;
		
		if (material_ptr->getColor().a() == 255) {
			opaqueQueue.push_back({mesh_ptr, material_ptr, &obj->transform().getWorldMatrix(), batchKey});
		} 
		else {
			float distToCamera = (cameraWorldPos - obj->transform().getWorldPosition()).length2();
			transparentQueue.push_back({mesh_ptr, material_ptr, &obj->transform().getWorldMatrix(), batchKey, distToCamera});
		}
	}

	std::sort(opaqueQueue.begin(), opaqueQueue.end(), [](const OpaqueRenderItem& ren1, const OpaqueRenderItem& ren2) {
		return ren1.batchKey < ren2.batchKey;
	});
	std::sort(transparentQueue.begin(), transparentQueue.end(), [](const TransparentRenderItem& ren1, const TransparentRenderItem& ren2) {
		return ren1.distance > ren2.distance;
	});

	static std::vector<Mxm::Mat4> matrixBatch;
	
	if (!opaqueQueue.empty()) {
		matrixBatch.clear();
		uint64_t currentBatchKey = opaqueQueue[0].batchKey;
    	const MeshComponent* currentMesh = opaqueQueue[0].meshComp;
     	const Material* currentMaterial = opaqueQueue[0].materialComp;
	
		for (const OpaqueRenderItem& ren : opaqueQueue) {
			if (currentBatchKey != ren.batchKey) {
				_meshRenderer->drawMeshInstanced(matrixBatch, currentMesh, currentMaterial);
				matrixBatch.clear();
	
				currentBatchKey = ren.batchKey;
				currentMesh = ren.meshComp;
				currentMaterial = ren.materialComp;
			}
			matrixBatch.push_back(*ren.worldMatrix);
		}
		if (!matrixBatch.empty()) {
        	_meshRenderer->drawMeshInstanced(matrixBatch, currentMesh, currentMaterial);
		}
	}

	for (const auto& obj : activeScene->getGameObjects()) {
		if (!obj->getActive()) continue;

		auto skybox_ptr = obj->getComponent<SkyBox>();
		if (!skybox_ptr) continue;

		_meshRenderer->drawSkyBox(skybox_ptr);
	}

	if (!transparentQueue.empty()) {
		matrixBatch.clear();
		uint64_t currentBatchKey = transparentQueue[0].batchKey;
    	const MeshComponent* currentMesh = transparentQueue[0].meshComp;
     	const Material* currentMaterial = transparentQueue[0].materialComp;
	
		for (const TransparentRenderItem& ren : transparentQueue) {
			if (currentBatchKey != ren.batchKey) {
				_meshRenderer->drawMeshInstanced(matrixBatch, currentMesh, currentMaterial);
				matrixBatch.clear();
	
				currentBatchKey = ren.batchKey;
				currentMesh = ren.meshComp;
				currentMaterial = ren.materialComp;
			}
			matrixBatch.push_back(*ren.worldMatrix);
		}
		if (!matrixBatch.empty()) {
        	_meshRenderer->drawMeshInstanced(matrixBatch, currentMesh, currentMaterial);
		}
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

	renderOpaqueTransparent(camera);
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

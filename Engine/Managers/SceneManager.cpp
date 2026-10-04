#include "SceneManager.h"
#include "../Core/Logger.h"

Scene* SceneManager::createScene(const std::string& name) {
	auto scene = std::make_unique<Scene>();

	Scene* rawPtr = scene.get();

	_scenes[name] = std::move(scene);

	return rawPtr;
}

void SceneManager::setActiveScene(Scene* scene) {
	if (scene) _pendingActiveScene = scene;
}
void SceneManager::setActiveScene(const std::string& name) {
	auto scene = _scenes.find(name);
	if (scene != _scenes.end()) {
		setActiveScene(scene->second.get());
	}
}

Scene* SceneManager::getActiveScene() const {
	return getScene(_activeSceneName);
}
Scene* SceneManager::getScene(const std::string& name) const {
	auto scene = _scenes.find(name);
	if (scene != _scenes.end()) {
		return scene->second.get();
	}
	Logger::getInstance().log(LogType::Fatal, "getActiveScene error GameManager");
	return nullptr;
}

void SceneManager::processPendingScene() {
	if (!_pendingActiveScene) return;

	for (const auto& s : _scenes) {
		Scene* scenePtr = s.second.get();
		if (scenePtr == _pendingActiveScene) {
			scenePtr->start();
			_activeSceneName = s.first;
			Logger::getInstance().log(LogType::Message, "Scene index activated: " + _activeSceneName);
			break;
		}
	}

	_pendingActiveScene = nullptr;
}
bool SceneManager::hasPendingScene() {
	return _pendingActiveScene;
}

void SceneManager::removeScene(Scene* scene) {
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it) {
		if (it->second.get() == scene) {

			if (it->first == _activeSceneName) {
				_activeSceneName = "";
			}

			_scenes.erase(it);
			break;
		}
	}
}
void SceneManager::removeScene(const std::string& name) {
	auto scene = _scenes.find(name);
	if (scene != _scenes.end()) {
		if (name == _activeSceneName) {
			_activeSceneName = "";
		}

		_scenes.erase(name);
	}
}
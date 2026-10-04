#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../ComponentSystem/Scene.h"

#include <unordered_map>
#include <memory>
#include <string>

class SceneManager final
{
private:
	std::unordered_map<std::string, std::unique_ptr<Scene>> _scenes;
	Scene* _pendingActiveScene = nullptr;
	std::string _activeSceneName;

	SceneManager() = default;
	~SceneManager() = default;

	void processPendingScene();
	bool hasPendingScene();
	friend class Application;
public:
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

	static SceneManager& getInstance() {
		static SceneManager manager;
		return manager;
	}

	Scene* createScene(const std::string& name);
	Scene* getActiveScene() const;
	Scene* getScene(const std::string& name) const;

	void setActiveScene(Scene* scene);
	void setActiveScene(const std::string& name);
	void removeScene(Scene* scene);
	void removeScene(const std::string& name);

	const std::string& getActiveSceneName() const noexcept { return _activeSceneName; }
};

#endif // !SCENEMANAGER_H

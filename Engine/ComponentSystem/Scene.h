#ifndef SCENE_H
#define SCENE_H

#include "Object/GameObject.h"
#include "Components/MeshComponent.h"
#include "../Animation/Animator.h"
#include "../Geometry/IntersectionInfo.h"

#include "Components/PointLight.h"
#include "Components/DirectionLight.h"

#include <unordered_set>
#include <unordered_map>

class Collider;
class RigidBody;

class Scene final
{
private:
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
	
	GameObject* _mainCamera = nullptr;
	
	Animator _animator;

	mutable std::vector<PointLight*> _pointLightsCache;
	mutable DirectionLight* _dirLightCache = nullptr;

	Color _backgroundColor = Color();
	Color _ambientColor = Color();

	void updateRecursive(Transform* transform);
public:
	Scene() = default;
	~Scene() = default;

	void updateCollisions();

	GameObject* createObject(const std::string& name, const std::string& tag = "default");

	std::vector<GameObject*> getObjectsWithName(const std::string& name) const;
	GameObject* getFirstObjectWithName(const std::string& name) const;

	std::vector<GameObject*> getObjectsWithTag(const std::string& tag) const;
	GameObject* getFirstObjectWithTag(const std::string& tag) const;

	const std::vector<PointLight*>& getPointLights() const;
	const DirectionLight* getDirectionLight() const;
	void updateLightCache() const;

	void removeObject(GameObject* obj);
	void removeObjectsWithTag(const std::string& tag);
	void removeObjectsWithName(const std::string& name);

	void interpolatePhysics();
	void start();
	void update();
	void fixedUpdate();
	void updateAnimator();

	inline Animator& getAnimator() noexcept { return _animator; }

	std::vector<GameObject*> getGameObjects() const noexcept;
	void clear();

	void setMainCamera(GameObject* camera);
	GameObject* getMainCamera() const;

	bool rayCast(const Mxm::Vec3& origin, const Mxm::Vec3& dir, IntersectionInfo& out, const std::vector<std::string>& tags) const;

	void setAmbientColor(Color color) noexcept;
	void setBackgroundColor(Color color) noexcept;

	Color getAmbientColor() const noexcept;
	Color getBackgroundColor() const noexcept;
};

#endif // !SCENE_H

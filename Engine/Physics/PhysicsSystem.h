#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <Engine/ComponentSystem/Object/GameObject.h>
#include <Engine/ComponentSystem/Components/Collider.h>

class PhysicsSystem final
{
private:
   	struct CachedObject {
		GameObject* gameObject;
		Collider* collider;
	};
	std::vector<CachedObject> _cachedObjects;
	std::unordered_map<Collider*, std::vector<GameObject*>> _previousTriggerObjects;
	std::unordered_map<Collider*, std::vector<GameObject*>> _currentTriggerObjects;

	void processCollisionPair(const CachedObject& obj1, const CachedObject& obj2);
	void processTriggers();
    
   	PhysicsSystem() = default;
	~PhysicsSystem() = default;
public:
   	PhysicsSystem(const PhysicsSystem&) = delete;
	PhysicsSystem& operator=(const PhysicsSystem&) = delete;
	PhysicsSystem(PhysicsSystem&&) = delete;
	PhysicsSystem& operator=(PhysicsSystem&&) = delete;

	static PhysicsSystem& getInstance() noexcept {
		static PhysicsSystem sys;
		return sys;
	}

	void update(const std::vector<GameObject*> gameObjects);
};

#endif

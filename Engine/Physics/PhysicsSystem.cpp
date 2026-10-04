#include "PhysicsSystem.h"

#include "CollisionSystem.h"
#include "CollisionSolver.h"

#include <Engine/ComponentSystem/Components/RigidBody.h>

void PhysicsSystem::processCollisionPair(const CachedObject& obj1, const CachedObject& obj2) {
    auto* gameObject1 = obj1.gameObject;
    auto* collider1 = obj1.collider;
    auto* rigidbody1 = obj1.gameObject->rigidBody();

    auto* gameObject2 = obj2.gameObject;
    auto* collider2 = obj2.collider;
    auto* rigidbody2 = obj2.gameObject->rigidBody();

    if (!gameObject1 || !collider1 || !gameObject1->getActive()) return;
    if (!gameObject2 || !collider2 || !gameObject2->getActive()) return;
    
    if (!rigidbody1 && !rigidbody2) return;

    bool obj1IsTrigger = collider1->isTrigger();
    bool obj2IsTrigger = collider2->isTrigger();

    if (obj1IsTrigger && obj2IsTrigger) return;

    if (!Collider::checkAABB(collider1, collider2)) return;
    
    auto collision = CollisionSystem::getInstance().gjkCollision(collider1, collider2);
    if (!collision.first) return;

    if (!obj1IsTrigger && !obj2IsTrigger) {
        if (rigidbody1) rigidbody1->setIsCollision(true);
        if (rigidbody2) rigidbody2->setIsCollision(true);
    }

    if (!obj1IsTrigger && !obj2IsTrigger) {
        CollisionResult result = CollisionSystem::getInstance().epaAlgorithm(collider1, collider2, collision.second);

        if (rigidbody1 && !rigidbody2) {
            CollisionSolver::getInstance().resolveCollisionStatic(rigidbody1, result);
            collider1->collisionCallback(gameObject2, result);
        }
        else if (rigidbody2 && !rigidbody1) {
            result.normal = -result.normal;

            CollisionSolver::getInstance().resolveCollisionStatic(rigidbody2, result);
            collider2->collisionCallback(gameObject1, result);
        }
        else if (rigidbody1 && rigidbody2) {
            CollisionSolver::getInstance().resolveCollisionDynamic(rigidbody1, rigidbody2, result);

            collider1->collisionCallback(gameObject2, result);
            result.normal = -result.normal;
            collider2->collisionCallback(gameObject1, result);
        }
    }

    if (obj1IsTrigger) _currentTriggerObjects[collider1].push_back(gameObject2);
    if (obj2IsTrigger) _currentTriggerObjects[collider2].push_back(gameObject1);
}
void PhysicsSystem::processTriggers() {
    for (auto& [collider, newObjs] : _currentTriggerObjects) {
        for (auto& obj : newObjs) {
            if (!_previousTriggerObjects.count(collider)) {
                collider->triggerOnCallback(obj);
            }

            collider->triggerStayCallback(obj);
        }
    }

    for (auto& [collider, prevObjs] : _previousTriggerObjects) {
        for (auto& obj : prevObjs) {
            if (!_currentTriggerObjects.count(collider)) {
                collider->triggerExitCallback(obj);
            }
        }
    }
}

void PhysicsSystem::update(const std::vector<GameObject*> gameObjects) {
    _cachedObjects.clear();

    for (auto& obj : gameObjects) {
        if (!obj->getActive()) continue;

        auto collider = obj->getComponent<Collider>();
        if (!collider) continue;

        if (obj->rigidBody()) obj->rigidBody()->setIsCollision(false);
        _cachedObjects.push_back({ obj, collider});
    }

    _previousTriggerObjects = std::move(_currentTriggerObjects);
    _currentTriggerObjects.clear();
    
    for (size_t i = 0; i < _cachedObjects.size(); ++i) {
        for (size_t j = i + 1; j < _cachedObjects.size(); ++j) {
            processCollisionPair(_cachedObjects[i], _cachedObjects[j]);
        }
    }

    processTriggers();
}

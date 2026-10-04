#include "Scene.h"

#include "Components/Camera.h"
#include "Components/Collider.h"
#include "Components/MeshComponent.h"
#include "Components/RigidBody.h"

#include "../Physics/PhysicsSystem.h"
#include "../Managers/EventManager.h"

void Scene::updateCollisions() {
    PhysicsSystem::getInstance().update(getGameObjects());
}

GameObject* Scene::createObject(const std::string& name, const std::string& tag) {
    _gameObjects.push_back(std::make_unique<GameObject>(name, tag));
    return _gameObjects.back().get();
}

std::vector<GameObject*> Scene::getObjectsWithName(const std::string& name) const {
    std::vector<GameObject*> result;

    for (const auto& obj : _gameObjects) {
        if (obj->getName() == name) {
            result.push_back(obj.get());
        }
    }

    return result;
}
GameObject* Scene::getFirstObjectWithName(const std::string& name) const {
    auto objects = getObjectsWithName(name);
    return objects.empty() ? nullptr : *objects.begin();
}

std::vector<GameObject*> Scene::getObjectsWithTag(const std::string& tag) const {
    std::vector<GameObject*> result;

    for (const auto& obj : _gameObjects) {
        if (obj->getTag() == tag) {
            result.push_back(obj.get());
        }
    }

    return result;
}
GameObject* Scene::getFirstObjectWithTag(const std::string& tag) const {
    auto objects = getObjectsWithTag(tag);
    return objects.empty() ? nullptr : *objects.begin();
}

const std::vector<PointLight*>& Scene::getPointLights() const {
    return _pointLightsCache;
}
const DirectionLight* Scene::getDirectionLight() const {
    return _dirLightCache;
}
void Scene::updateLightCache() const {
    _pointLightsCache.clear();
    _dirLightCache = nullptr;

    for (const auto& obj : _gameObjects) {
        if (auto light = obj->getComponent<PointLight>()) {
            _pointLightsCache.push_back(light);
        }
        if (auto dirLight = obj->getComponent<DirectionLight>()) {
            _dirLightCache = dirLight;
        }
    }
}

void Scene::removeObject(GameObject* obj) {
    obj->makeRemovePending();
}
void Scene::removeObjectsWithTag(const std::string& tag) {
    for (auto& obj : _gameObjects) {
        if (tag == obj->getTag()) {
            obj->makeRemovePending();
        }
    }
}
void Scene::removeObjectsWithName(const std::string& name) {
    for (auto& obj : _gameObjects) {
        if (name == obj->getName()) {
            obj->makeRemovePending();
        }
    }
}

void Scene::updateRecursive(Transform* transform) {
    if (!transform) return;

    transform->getOwner()->updateComponents();

    for (auto t : transform->getChildren()) {
        if (!t) continue;
        updateRecursive(t);
    }
}

void Scene::interpolatePhysics() {
    //Physics interpolating
    for (auto& obj : _gameObjects) {
        if (!obj->getActive()) continue;
        
        if (obj->rigidBody()) {
            obj->rigidBody()->interpolate();
        }
    }
}
void Scene::start() {
	for (auto& obj : _gameObjects) {
		obj->startComponents();
	}
    updateLightCache();
    EventManager::getInstance().poll("light_update");
}
void Scene::update() {
    size_t count = _gameObjects.size();
    
    for (size_t i = 0; i < count; ++i) {
        auto* obj = _gameObjects[i].get();
    
        if (!obj->getActive())
            continue;
    
        if (obj->transform().getParent())
            continue;
    
        updateRecursive(&obj->transform());
    }

    std::erase_if(_gameObjects, [](const std::unique_ptr<GameObject>& obj) {
        return obj->isRemovePending();
    });
    
    if (EventManager::getInstance().poll("light_update")) updateLightCache();
}
void Scene::fixedUpdate() {
    for (auto& obj : _gameObjects) {
        if (!obj->getActive()) continue;
        obj->fixedUpdateComponents();
    }
}

void Scene::updateAnimator() {
    _animator.update();
}

std::vector<GameObject*> Scene::getGameObjects() const noexcept {
    std::vector<GameObject*> result;
    for (const auto& obj : _gameObjects) {
        result.push_back(obj.get());
    }
    return result;
}
void Scene::clear() {
    _gameObjects.clear();
    _mainCamera = nullptr;
}

void Scene::setMainCamera(GameObject* camera) {
	if (camera->hasComponent<Camera>()) _mainCamera = camera;
}
GameObject* Scene::getMainCamera() const {
    return _mainCamera;
}

bool Scene::rayCast(const Mxm::Vec3& origin, const Mxm::Vec3& dir, IntersectionInfo& out, const std::vector<std::string>& tags) const {
    bool hit = false;
    float closestDistance = std::numeric_limits<float>::max();
    IntersectionInfo temp;

    for (const auto& obj : _gameObjects) {
        auto mesh_ptr = obj->getComponent<MeshComponent>();
        auto collider_ptr = obj->getComponent<Collider>();
        if (!mesh_ptr || !collider_ptr) continue;

        if (std::find(tags.begin(), tags.end(), obj->getTag()) == tags.end()) continue;

        Mxm::Mat4 inverseModel = obj->transform().getInverseWorldMatrix();
        Mxm::Vec3 invOrigin = (inverseModel * Mxm::Vec4(origin, 1.0f)).toVec3();
        Mxm::Vec3 invDir = (inverseModel * Mxm::Vec4(dir, 0.0f)).toVec3();

        if (!collider_ptr->getLocalAABB().isIntersection(invOrigin, invDir)) continue;

        if (mesh_ptr->intersection(invOrigin, invDir, temp)) {
            if (temp.distance < closestDistance) {
                closestDistance = temp.distance;
                out = temp;
                hit = true;
            }
        }
    }

    return hit;
}

void Scene::setAmbientColor(Color color) noexcept {
    _ambientColor = color;
}
void Scene::setBackgroundColor(Color color) noexcept {
    _backgroundColor = color;
}

Color Scene::getAmbientColor() const noexcept {
    return _ambientColor;
}
Color Scene::getBackgroundColor() const noexcept {
    return _backgroundColor;
}

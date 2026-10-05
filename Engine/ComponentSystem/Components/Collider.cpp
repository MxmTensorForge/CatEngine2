#include "Collider.h"
#include "../Object/GameObject.h"
#include "RigidBody.h"
#include "MeshComponent.h"

void Collider::start() {
	if (_needsRecalcAABB) {
		generateLocalAABB();
		_needsRecalcAABB = false;
	}
}
void Collider::recaclAABB() noexcept {
   	if (_needsRecalcAABB) {
		generateLocalAABB();
		_needsRecalcAABB = false;
	}
   
	auto* rb = getObject()->rigidBody();
   
	const Mxm::Mat4& worldMatrix = rb ? rb->getPhysicsWorldMatrix() : getObject()->transform().getWorldMatrix();
	
	_worldAABB.extent = (worldMatrix.abs() * Mxm::Vec4(_localAABB.extent, 0.0f)).toVec3();
	_worldAABB.center = (worldMatrix * Mxm::Vec4(_localAABB.center, 1.0f)).toVec3();
}

AABB Collider::calculateAABBFromMesh(const std::vector<Mxm::Vec3>& vertices) noexcept {
	Mxm::Vec3 min = Mxm::Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	Mxm::Vec3 max = Mxm::Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (const auto& v : vertices) {
		min.x = fminf(min.x, v.x);
		min.y = fminf(min.y, v.y);
		min.z = fminf(min.z, v.z);

		max.x = fmaxf(max.x, v.x);
		max.y = fmaxf(max.y, v.y);
		max.z = fmaxf(max.z, v.z);
	}
	AABB aabb;
	aabb.center = (min + max) * 0.5f;
	aabb.extent = (max - min) * 0.5f;

	return aabb;
}

bool Collider::checkAABB(Collider* collider1,Collider* collider2) noexcept {
    collider1->recaclAABB();
    collider2->recaclAABB();
    
	const AABB& aabb1 = collider1->_worldAABB;
	const AABB& aabb2 = collider2->_worldAABB;

	Mxm::Vec3 diff = (aabb1.center - aabb2.center).abs();
	Mxm::Vec3 maxDist = aabb1.extent + aabb2.extent;

	return (diff.x <= maxDist.x && diff.y <= maxDist.y && diff.z <= maxDist.z);
}

void Collider::generateLocalAABB() noexcept {
    if (!_shape) return;

    Mxm::Vec3 min;
    Mxm::Vec3 max;

    max.x = _shape->support(Mxm::Vec3(1.0f, 0.0f, 0.0f)).x;
    min.x = _shape->support(Mxm::Vec3(-1.0f, 0.0f, 0.0f)).x;

    max.y = _shape->support(Mxm::Vec3(0.0f, 1.0f, 0.0f)).y;
    min.y = _shape->support(Mxm::Vec3(0.0f, -1.0f, 0.0f)).y;

    max.z = _shape->support(Mxm::Vec3(0.0f, 0.0f, 1.0f)).z;
    min.z = _shape->support(Mxm::Vec3(0.0f, 0.0f, -1.0f)).z;

    _localAABB.center = (min + max) * 0.5f;
    _localAABB.extent = (max - min) * 0.5f + 0.03f;
}


void Collider::generateFromMesh() {
	auto mesh = getObject()->getComponent<MeshComponent>();
	if (!mesh) return;

	setColliderShape<ConvexHullShape>(mesh->getData());
}
void Collider::generateBoxFromMesh() {
	auto mesh = getObject()->getComponent<MeshComponent>();
	if (!mesh) return;

	AABB aabb = calculateAABBFromMesh(mesh->getVertices());
	setColliderShape<BoxShape>(aabb.center, aabb.extent);
}

Mxm::Vec3 Collider::support(const Mxm::Vec3& direction) const noexcept {
	if (!_shape) return Mxm::Vec3();
	return _shape->support(direction);
}

void Collider::clearCallbacks() noexcept {
	_triggerOnCallback = nullptr;
	_triggerExitCallback = nullptr;
	_triggerStayCallback = nullptr;
	_collisionOnCallback = nullptr;
}

void Collider::update() {
}

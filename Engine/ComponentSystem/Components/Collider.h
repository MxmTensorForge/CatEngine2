#ifndef COLLIDER_H
#define COLLIDER_H

#include "../Component.h"
#include "../../Mxm/Vec3.h"
#include "../../Geometry/AABB.h"
#include "../../Geometry/MeshData.h"
#include "../../Physics/CollisionResult.h"

#include "../../Physics/Colliders/BoxShape.h"
#include "../../Physics/Colliders/ConvexHullShape.h"
#include "../../Physics/Colliders/SphereShape.h"
#include "../../Physics/Colliders/CapsuleShape.h"

#include <vector>
#include <memory>
#include <functional>

class Collider final : public Component
{
private:
	std::unique_ptr<ColliderShape> _shape;

	AABB _localAABB{};
	AABB _worldAABB{};

	bool _needsRecalcAABB = true;
	bool _isTrigger = false;

	using TriggerCallback = std::function<void(GameObject*)>;
	TriggerCallback _triggerOnCallback;
	TriggerCallback _triggerExitCallback;
	TriggerCallback _triggerStayCallback;

	using CollisionCallback = std::function<void(GameObject*, const CollisionResult&)>;
	CollisionCallback _collisionOnCallback;
public:
    void start() override;
	void update() override;
	void recaclAABB() noexcept;

	static AABB calculateAABBFromMesh(const std::vector<Mxm::Vec3>& verts) noexcept;
	static bool checkAABB(Collider* collider1, Collider* collider2) noexcept;

	void generateLocalAABB() noexcept;
	const AABB& getLocalAABB() const noexcept { return _localAABB; }

	template <typename ShapeType, typename... Args>
	void setColliderShape(Args&&... args) {
		_shape = std::make_unique<ShapeType>(std::forward<Args>(args)...);
		_needsRecalcAABB = true;
	}

	void generateFromMesh();
	void generateBoxFromMesh();

	Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept;

	void setTriggerOnCallback(const TriggerCallback& c) noexcept { _triggerOnCallback = c; }
	void triggerOnCallback(GameObject* obj) noexcept { if (_triggerOnCallback && _isTrigger) _triggerOnCallback(obj); }

	void setTriggerExitCallback(const TriggerCallback& c) noexcept { _triggerExitCallback = c; }
	void triggerExitCallback(GameObject* obj) noexcept { if (_triggerExitCallback && _isTrigger) _triggerExitCallback(obj); }

	void setTriggerStayCallback(const TriggerCallback& c) noexcept { _triggerStayCallback = c; }
	void triggerStayCallback(GameObject* obj) noexcept { if (_triggerStayCallback && _isTrigger) _triggerStayCallback(obj); }

	void setCollisionCallback(const CollisionCallback& c) noexcept { _collisionOnCallback = c; }
	void collisionCallback(GameObject* obj, const CollisionResult& result) noexcept { if (_collisionOnCallback) _collisionOnCallback(obj, result); }

	void clearCallbacks() noexcept;

	bool isTrigger() const noexcept { return _isTrigger; }
	void setTrigger(bool state) noexcept { _isTrigger = state; }
};

#endif // !COLLIDER_H

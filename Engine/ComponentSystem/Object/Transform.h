#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Component.h"

#include "../../Mxm/Mat4.h"
#include <memory>
#include <vector>

class GameObject;

class Transform final
{
private:
	Mxm::Vec3 _position{};
	Mxm::Vec3 _scale = Mxm::Vec3(1.0f,1.0f,1.0f);

	Mxm::Quat _rotation = Mxm::Quat::identity();
	mutable Mxm::Quat _worldRotation = Mxm::Quat::identity();

	mutable bool _isDirty = true;
	mutable Mxm::Mat4 _model;
	mutable Mxm::Mat4 _world;

	Transform* _parent = nullptr;
	std::vector<Transform*> _children;

	GameObject* _owner = nullptr;

	void setPositionInternal(const Mxm::Vec3& vec) noexcept;
	friend class RigidBody;
public:
	Transform(const Transform&) = delete;
	Transform& operator=(const Transform&) = delete;

	Transform() = default;
	~Transform() = default;

	void setOwner(GameObject* obj) noexcept { if (!_owner && obj) _owner = obj; }
	GameObject* getOwner() const noexcept { return _owner; }

	void translate(const Mxm::Vec3& vec) noexcept;
	void rotate(const Mxm::Quat& quat) noexcept;
	void scale(const Mxm::Vec3& vec) noexcept;

	void setPosition(const Mxm::Vec3& vec) noexcept;
	void setRotation(const Mxm::Quat& quat) noexcept;
	void setScale(const Mxm::Vec3& vec) noexcept;

	const Mxm::Vec3& getPosition() const noexcept;
	const Mxm::Quat& getRotation() const noexcept;
	const Mxm::Vec3& getScale() const noexcept;

	Mxm::Vec3 getWorldPosition() const noexcept;
	Mxm::Quat getWorldRotation() const noexcept;
	Mxm::Vec3 getWorldScale() const noexcept;

	Mxm::Vec3 inBasisRotate(const Mxm::Vec3& vec) const noexcept;

	bool isChildOf(Transform* potentialParent) const noexcept;

	void setParent(Transform* newParent) noexcept;
	Transform* getParent() const noexcept { return _parent; }

	void addChild(Transform* child) noexcept;
	void removeChild(Transform* child) noexcept;
	const std::vector<Transform*>& getChildren() const noexcept { return _children; }

	const Mxm::Vec3 getRight() const noexcept;
	const Mxm::Vec3 getUp() const noexcept;
	const Mxm::Vec3 getForward() const noexcept;

	const Mxm::Mat4& getModelMatrix() const noexcept;
	const Mxm::Mat4& getWorldMatrix() const noexcept;

	Mxm::Mat4 getInverseModelMatrix() const noexcept;
	Mxm::Mat4 getInverseWorldMatrix() const noexcept;
private:
	void markDirty() noexcept;
};

#endif // !TRANSFORM_H

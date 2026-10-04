#include "Transform.h"
#include "GameObject.h"
#include "../Components/RigidBody.h"

#include <algorithm>

void Transform::setPositionInternal(const Mxm::Vec3& vec) noexcept {
    _position = vec;
    markDirty();
}

void Transform::translate(const Mxm::Vec3& vec) noexcept {
    if (auto* rb = _owner->rigidBody()) {
        rb->translate(vec);
        return;
    }
    
	_position += vec;
	markDirty();
}
void Transform::rotate(const Mxm::Quat& quat) noexcept {
	_rotation = (quat * _rotation).normalized();
	markDirty();
}
void Transform::scale(const Mxm::Vec3& vec) noexcept {
	_scale *= vec;
	markDirty();
}

void Transform::setPosition(const Mxm::Vec3& vec) noexcept {
    if (auto* rb = _owner->rigidBody()) {
        rb->setPosition(vec);
        return;
    }
    
	_position = vec;
	markDirty();
}
void Transform::setRotation(const Mxm::Quat& quat) noexcept {
	_rotation = quat.normalized();
	markDirty();
}
void Transform::setScale(const Mxm::Vec3& vec) noexcept {
	_scale = vec;
	markDirty();
}

const Mxm::Vec3 Transform::getRight() const noexcept {
	getWorldMatrix();
	return _world.col(0).toVec3().normalized();
}
const Mxm::Vec3 Transform::getUp() const noexcept {
	getWorldMatrix();
	return _world.col(1).toVec3().normalized();
}
const Mxm::Vec3 Transform::getForward() const noexcept {
	getWorldMatrix();
	return _world.col(2).toVec3().normalized();
}

Mxm::Vec3 Transform::getWorldPosition() const noexcept {
	getWorldMatrix();
	return _world.col(3).toVec3();
}
Mxm::Quat Transform::getWorldRotation() const noexcept {
	if (_parent) {
		_worldRotation = _parent->getWorldRotation() * _rotation;
	}
	else {
		_worldRotation = _rotation;
	}
	return _worldRotation;
}
Mxm::Vec3 Transform::getWorldScale() const noexcept {
	const Mxm::Mat4& world = getWorldMatrix();

	float scaleX = world.col(0).toVec3().length();
	float scaleY = world.col(1).toVec3().length();
	float scaleZ = world.col(2).toVec3().length();

	return Mxm::Vec3(scaleX, scaleY, scaleZ);
}

Mxm::Vec3 Transform::inBasisRotate(const Mxm::Vec3& vec) const noexcept {
	return getRight() * vec.x + getUp() * vec.y + getForward() * vec.z;
}

bool Transform::isChildOf(Transform* potentialParent) const noexcept {
	if (!potentialParent) return false;;

	const Transform* current = this;
	while (current) {
		if (current == potentialParent) return true;
		current = current->getParent();
	}
	return false;
}

void Transform::setParent(Transform* newParent) noexcept {
	auto oldParent = _parent;
	if (oldParent == newParent || this == newParent) return;

	if (newParent->isChildOf(this) && newParent) {
		return;
	}

	if (oldParent) oldParent->removeChild(this);
	_parent = newParent;

	if (newParent) newParent->_children.push_back(this);
	markDirty();
}

void Transform::addChild(Transform* child) noexcept {
	if (!child || child == this) return;

	child->setParent(this);
}
void Transform::removeChild(Transform* child) noexcept {
	if (!child) return;
	_children.erase(std::find(_children.begin(), _children.end(), child));
}

const Mxm::Mat4& Transform::getModelMatrix() const noexcept {
	if (_isDirty) {
		_model = Mxm::Mat4::translation(_position) * Mxm::Mat4::rotation(_rotation) * Mxm::Mat4::scaling(_scale);
		_isDirty = false;
	}

	return _model;
}
const Mxm::Mat4& Transform::getWorldMatrix() const noexcept {
	if (_isDirty) {
		getModelMatrix();
		if (_parent) {
			_world = _parent->getWorldMatrix() * _model;
		}
		else {
			_world = _model;
		}
	}
	return _world;
}

Mxm::Mat4 Transform::getInverseModelMatrix() const noexcept {
	Mxm::Mat4 inverse;

	Mxm::Vec3 invScale = Mxm::Vec3(1.0f / _scale.x, 1.0f / _scale.y, 1.0f / _scale.z);
	inverse = Mxm::Mat4::scaling(invScale) * Mxm::Mat4::rotation(_rotation).transposed() * Mxm::Mat4::translation(-_position);

	return inverse;
}
Mxm::Mat4 Transform::getInverseWorldMatrix() const noexcept {
	Mxm::Mat4 myInv = getInverseModelMatrix();
	if (_parent) {
		return myInv * _parent->getInverseWorldMatrix();
	}
	return myInv;
}

void Transform::markDirty() noexcept {
	_isDirty = true;
	for (auto& child : _children) {
		if (child) {
			child->markDirty();
		}
	}
}

const Mxm::Vec3& Transform::getPosition() const noexcept {
	return _position;
}
const Mxm::Quat& Transform::getRotation() const noexcept {
	return _rotation;
}
const Mxm::Vec3& Transform::getScale() const noexcept {
	return _scale;
}

#include "RigidBody.h"

#include "../Object/Transform.h"
#include "../Object/GameObject.h"

#include "../../Core/Time.h"

RigidBody::RigidBody() {
}

void RigidBody::correctPosition(const Mxm::Vec3& vec) noexcept {
    _currentPhysicsPos += vec;
}
void RigidBody::translate(const Mxm::Vec3& vec) noexcept {
    _currentPhysicsPos += vec;
    _previousPhysicsPos += vec;
}
void RigidBody::setPosition(const Mxm::Vec3& vec) noexcept {
    _currentPhysicsPos = vec;
    _previousPhysicsPos = vec;
}
const Mxm::Vec3& RigidBody::getPosition() const noexcept {
    return _currentPhysicsPos;
}
Mxm::Mat4 RigidBody::getPhysicsModelMatrix() const noexcept {
    const Mxm::Vec3& scale = getObject()->transform().getScale();
    const Mxm::Quat& rotation = getObject()->transform().getRotation();

    return Mxm::Mat4::translation(_currentPhysicsPos) * 
           Mxm::Mat4::rotation(rotation) *
           Mxm::Mat4::scaling(scale);
}
Mxm::Mat4 RigidBody::getPhysicsWorldMatrix() const noexcept {
    return getPhysicsModelMatrix(); //TODO
}

void RigidBody::init() {
    _previousPhysicsPos = getObject()->transform().getPosition();
    _currentPhysicsPos = getObject()->transform().getPosition();
}
void RigidBody::fixedUpdate() {
	Mxm::Vec3 acceleration = _gravity;
	_velocity += acceleration * Time::fixedDeltaTime();

	_previousPhysicsPos = _currentPhysicsPos;
	_currentPhysicsPos += _velocity * Time::fixedDeltaTime();
}
void RigidBody::interpolate() {
    getObject()->transform().setPositionInternal(_previousPhysicsPos.lerp(_currentPhysicsPos, Time::physicsAlpha()));
	//getObject()->transform().setPositionInternal(_currentPhysicsPos);
}

void RigidBody::addImpulse(const Mxm::Vec3& vec) noexcept { _velocity += vec / _mass; }

void RigidBody::setGravity(const Mxm::Vec3& vec) noexcept { _gravity = vec; }
const Mxm::Vec3& RigidBody::getGravity() const noexcept { return _gravity; }

void RigidBody::setVelocity(const Mxm::Vec3& vec) noexcept { _velocity = vec; }
const Mxm::Vec3& RigidBody::getVelocity() const noexcept { return _velocity; }

void RigidBody::setMass(float value) noexcept { _mass = fmaxf(value, 0.001f); }
float RigidBody::getMass() const noexcept { return _mass; }

void RigidBody::setFriction(float value) noexcept { _friction = value; }
float RigidBody::getFriction() const noexcept { return _friction; }

void RigidBody::setRestitution(float value) noexcept { _restitution = value; }
float RigidBody::getRestitution() const noexcept { return _restitution; }

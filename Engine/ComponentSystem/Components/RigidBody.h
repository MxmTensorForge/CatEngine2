#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../Component.h"
#include "../../Physics/CollisionResult.h"
#include "../../Mxm/Mat4.h"

#include <vector>
#include <memory>
#include <deque>
#include <utility>
#include <functional>

class RigidBody final : public Component
{
private:
    Mxm::Vec3 _currentPhysicsPos{};
    Mxm::Vec3 _previousPhysicsPos{};
    
	Mxm::Vec3 _gravity{0.0f, -9.81f, 0.0f};
	Mxm::Vec3 _velocity{};

	float _mass = 1.0f;

	float _friction{};
	float _restitution = 0.0f;

	bool _isCollision{};
public:
    RigidBody();

    void correctPosition(const Mxm::Vec3& vec) noexcept;
    void translate(const Mxm::Vec3& vec) noexcept;
    void setPosition(const Mxm::Vec3& vec) noexcept;
    const Mxm::Vec3& getPosition() const noexcept;

    Mxm::Mat4 getPhysicsModelMatrix() const noexcept;
    Mxm::Mat4 getPhysicsWorldMatrix() const noexcept;
    
	void addImpulse(const Mxm::Vec3& vec) noexcept;
	void addImpulseInPoint(const Mxm::Vec3& point, Mxm::Vec3& vec) noexcept;

	void setGravity(const Mxm::Vec3& vec) noexcept;
	const Mxm::Vec3& getGravity() const noexcept;

	void setVelocity(const Mxm::Vec3& vec) noexcept;
	const Mxm::Vec3& getVelocity() const noexcept;

	void setMass(float value) noexcept;
	float getMass() const noexcept;

	void setFriction(float value) noexcept;
	float getFriction() const noexcept;

	void setRestitution(float value) noexcept;
	float getRestitution() const noexcept;

	void setAngularDamping(float value) noexcept;
	float getAngularDamping() const noexcept;

	bool isCollision() const noexcept { return _isCollision; }
	void setIsCollision(bool state) noexcept { _isCollision = state; }

	void init() override;
	void fixedUpdate() override;
	void interpolate();
};

#endif // !RIGIDBODY_H

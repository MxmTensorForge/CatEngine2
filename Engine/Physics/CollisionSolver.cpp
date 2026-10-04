#include "CollisionSolver.h"

#include "../ComponentSystem/Object/GameObject.h"
#include "../ComponentSystem/Components/RigidBody.h"

#include "../Core/Logger.h"

void CollisionSolver::resolveCollisionStatic(RigidBody* rb, const CollisionResult& result) {
	Mxm::Vec3 move = result.normal * result.depth;
	rb->correctPosition(-move);

	float restitution = rb->getRestitution();
	float friction = rb->getFriction();

	Mxm::Vec3 vel = rb->getVelocity();
	Mxm::Vec3 vel_n = result.normal * result.normal.dot(vel);
	Mxm::Vec3 vel_t = vel - vel_n;

	vel_n = -vel_n * restitution;
	vel_t = vel_t * (1.0f - friction);

	vel = vel_n + vel_t;

	rb->setVelocity(vel);

	if (result.depth > 0.3f) {
		Logger::getInstance().log(LogType::Warning, "COLLISION PENEPRATION > 0.3");
	}
}
void CollisionSolver::resolveCollisionDynamic(RigidBody* rb1, RigidBody* rb2, const CollisionResult& result) {
	Mxm::Vec3 move = result.normal * result.depth;

	float mass1 = rb1->getMass();
	float mass2 = rb2->getMass();
	float totalMass = mass1 + mass2;

	if (totalMass < Mxm::Consts::EPS) return;
	float invTotalMass = 1.0f / totalMass;

	float moveRatio1 = mass2 * invTotalMass;
	Mxm::Vec3 move1 = -move * moveRatio1;

	float moveRatio2 = mass1 * invTotalMass;
	Mxm::Vec3 move2 = move * moveRatio2;

	rb1->correctPosition(move1);
	rb2->correctPosition(move2);

	Mxm::Vec3 v1 = rb1->getVelocity();
	Mxm::Vec3 v2 = rb2->getVelocity();

	Mxm::Vec3 v1_n = result.normal * v1.dot(result.normal);
	Mxm::Vec3 v2_n = result.normal * v2.dot(result.normal);
	Mxm::Vec3 v1_t = v1 - v1_n;
	Mxm::Vec3 v2_t = v2 - v2_n;

	float restitution = fminf(rb1->getRestitution(), rb2->getRestitution());

	Mxm::Vec3 u1_n = (v1_n * (mass1 - mass2 * restitution) + v2_n * mass2 * (1.0f + restitution)) * invTotalMass;
	Mxm::Vec3 u2_n = (v2_n * (mass2 - mass1 * restitution) + v1_n * mass1 * (1.0f + restitution)) * invTotalMass;

	float friction = sqrtf(rb1->getFriction() * rb2->getFriction());
	
    Mxm::Vec3 u1_t = v1_t * (1.0f - friction);
    Mxm::Vec3 u2_t = v2_t * (1.0f - friction);

	v1 = u1_t + u1_n;
	v2 = u2_t + u2_n;

	rb1->setVelocity(v1);
	rb2->setVelocity(v2);

	if (result.depth > 0.3f) {
		Logger::getInstance().log(LogType::Warning, "COLLISION PENEPRATION > 0.3");
	}
}

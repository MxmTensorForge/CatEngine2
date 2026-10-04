#ifndef COLLISIONSOLVER_H
#define COLLISIONSOLVER_H

#include "../Geometry/Triangle.h"

#include "CollisionResult.h"
#include "Simplex.h"

#include <utility>
#include <vector>

class Collider;
class RigidBody;

class CollisionSolver final
{
private:
	CollisionSolver() = default;
	~CollisionSolver() = default;
public:
	CollisionSolver(const CollisionSolver&) = delete;
	CollisionSolver& operator=(const CollisionSolver&) = delete;
	CollisionSolver(CollisionSolver&&) = delete;
	CollisionSolver& operator=(CollisionSolver&&) = delete;

	static CollisionSolver& getInstance() noexcept {
		static CollisionSolver sys;
		return sys;
	}
	
	void resolveCollisionStatic(RigidBody* rb, const CollisionResult& result);
	void resolveCollisionDynamic(RigidBody* rb1, RigidBody* rb2, const CollisionResult& result);
};

#endif // !COLLISIONSOLVER_H

#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H

#include "../Mxm/Vec3.h"

struct CollisionResult {
	Mxm::Vec3 normal;
	float depth;
};

#endif // !COLLISIONRESULT_H

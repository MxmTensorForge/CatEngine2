#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H

#include "../Mxm/Vec3.h"

struct CollisionResult {
    Mxm::Vec3 normal;
	float depth;

	Mxm::Vec3 contactA;
	Mxm::Vec3 contactB;
};

#endif // !COLLISIONRESULT_H

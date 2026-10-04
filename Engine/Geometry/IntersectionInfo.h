#ifndef INTERSECTIONINFO_H
#define INTERSECTIONINFO_H

#include "../ComponentSystem/Object/GameObject.h"

struct IntersectionInfo
{
	float distance;
	Mxm::Vec3 point;
	GameObject* gameObject;
	std::string tag;
};

#endif // !INTERSECTIONINFO_H

#include "MeshComponent.h"
#include "../../Geometry/Triangle.h"

#include "../../Managers/MeshManager.h"

#include "../../ComponentSystem/Object/GameObject.h"
#include "../../ComponentSystem/Components/RigidBody.h"

#include <string>

MeshComponent::MeshComponent(const std::string& modelName) : _mesh{ MeshManager::getInstance().getModel(modelName) } {}
void MeshComponent::setModelName(const std::string& modelName) noexcept {
    _mesh = MeshManager::getInstance().getModel(modelName);
}

bool MeshComponent::intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, IntersectionInfo& out) {
	const auto& vertices = getVertices();
	const auto& indices = getIndices();

	Mxm::Vec3 intersection_point;
	float dist{};

	float closest_distance = std::numeric_limits<float>::max();
	bool hit = false;
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		Mxm::Vec3 v0 = vertices[indices[i]];
		Mxm::Vec3 v1 = vertices[indices[i + 1]];
		Mxm::Vec3 v2 = vertices[indices[i + 2]];

		Triangle tri = Triangle(v0, v1, v2);

		if (tri.intersection(origin, dir, intersection_point, dist)) {
			if (dist < closest_distance) {
				closest_distance = dist;

				auto* obj = getObject();
				const auto& model = obj->transform().getWorldMatrix();

				Mxm::Vec3 position = obj->transform().getWorldPosition();
				if (obj->rigidBody()) position = obj->rigidBody()->getPosition();
				
				out = { dist, (model * Mxm::Vec4(intersection_point, 0.0f)).toVec3() + position, obj, obj->getTag()};
				hit = true;
			}
		}
	}
	return hit;
}

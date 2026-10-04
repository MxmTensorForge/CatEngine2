#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include "../Component.h"
#include "../../Geometry/MeshData.h"
#include "../../Geometry/IntersectionInfo.h"

#include <vector>
#include <string>
#include <memory>

struct MeshData;

class MeshComponent final : public Component
{
private:
	MeshData* _mesh;
public:
	MeshComponent(const std::string& modelName);
	void setModelName(const std::string& modelName) noexcept;

	const std::vector<Mxm::Vec3>& getVertices() const noexcept { return _mesh->vertices; }
	const std::vector<unsigned int>& getIndices() const noexcept { return _mesh->indices; }

	MeshData* getData() const noexcept { return _mesh; }

	bool intersection(const Mxm::Vec3& origin, const Mxm::Vec3& dir, IntersectionInfo& out);
};

#endif

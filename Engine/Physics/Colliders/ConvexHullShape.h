#ifndef CONVEXHULLSHAPE_H
#define CONVEXHULLSHAPE_H

#include "ColliderShape.h"
#include "../../Geometry/MeshData.h"

#include <vector>
#include <cfloat>

class ConvexHullShape final : public ColliderShape
{
private:
    MeshData* _meshData;
public:
    ConvexHullShape(MeshData* m) : _meshData{m} {}

	Mxm::Vec3 support(const Mxm::Vec3& direction) const noexcept override {
        float maxDot = -FLT_MAX;
        Mxm::Vec3 best;

        for (const auto& v : _meshData->vertices) {
            float d = v.dot(direction);
            if (d > maxDot) {
                maxDot = d;
                best = v;
            }
        }
        return best;
	}
};

#endif // !CONVEXHULLSHAPE_H

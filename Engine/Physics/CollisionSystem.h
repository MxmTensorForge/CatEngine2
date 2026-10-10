#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "CollisionResult.h"
#include "Simplex.h"
#include "FixedVector.h"
#include "MinkowskiTriangle.h"

#include <utility>
#include <vector>

class Collider;
class RigidBody;

class CollisionSystem final
{
private:
    struct Edge
    {
        MinkowskiPoint a, b;
        Edge reversed() const { return Edge{ b, a }; }

        bool operator==(const Edge& other) const {
            return (a.point == other.a.point && b.point == other.b.point);
        }
    };
    using Polytope = FixedVector<MinkowskiTriangle, 64>;

    Mxm::Vec3 furthestPoint(const Collider* collider, const Mxm::Vec3& dir);
    MinkowskiPoint minkowskiDifference(const Collider* collider1, const Collider* collider2, const Mxm::Vec3& dir);
    bool handleSimplex(Simplex& simplex, Mxm::Vec3& direction);

    std::pair<MinkowskiTriangle, float> findClosestFace(const Polytope& polytope);
    void expandPolytope(Polytope& polytope, const MinkowskiPoint& newPoint);

    CollisionSystem() = default;
    ~CollisionSystem() = default;
public:
    CollisionSystem(const CollisionSystem&) = delete;
    CollisionSystem& operator=(const CollisionSystem&) = delete;
    CollisionSystem(CollisionSystem&&) = delete;
    CollisionSystem& operator=(CollisionSystem&&) = delete;

    static CollisionSystem& getInstance() noexcept {
        static CollisionSystem sys;
        return sys;
    }

    std::pair<bool, Simplex> gjkCollision(const Collider* collider1, const Collider* collider2);
    CollisionResult epaAlgorithm(const Collider* collider1, const Collider* collider2, const Simplex& simplex);
};

#endif

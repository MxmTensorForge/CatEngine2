#include "CollisionSystem.h"

#include "../ComponentSystem/Object/GameObject.h"
#include "../ComponentSystem/Components/Collider.h"
#include "../ComponentSystem/Components/RigidBody.h"

Mxm::Vec3 CollisionSystem::furthestPoint(const Collider* collider, const Mxm::Vec3& dir) {
    Mxm::Mat4 worldMatrix = collider->getObject()->rigidBody() ? 
        collider->getObject()->rigidBody()->getPhysicsWorldMatrix() : collider->getObject()->transform().getWorldMatrix();
    
    Mxm::Vec3 localDir = (worldMatrix.transposed() * Mxm::Vec4(dir, 0.0f)).toVec3(); //я не знаю почему это работает, потому что обратная матрица даёт сбой

    Mxm::Vec3 furthestPoint = collider->support(localDir);

    return (worldMatrix * Mxm::Vec4(furthestPoint, 1.0f)).toVec3();
}
MinkowskiPoint CollisionSystem::minkowskiDifference(const Collider* collider1, const Collider* collider2, const Mxm::Vec3& dir) {
    MinkowskiPoint point;
    point.a = furthestPoint(collider1, dir);
    point.b = furthestPoint(collider2, -dir);
    point.point = point.a - point.b;
    
    return point;
}

bool CollisionSystem::handleSimplex(Simplex& simplex, Mxm::Vec3& direction) {
    const MinkowskiPoint& a = simplex[0];
    const MinkowskiPoint& b = simplex[1];
    Mxm::Vec3 ao = -a.toVec3();
    Mxm::Vec3 ab = b.toVec3() - a.toVec3();

    if (simplex.size() == 2) {
        direction = ab.cross(ao).cross(ab);

        return true;
    }
    else if (simplex.size() == 3) {
        const MinkowskiPoint& c = simplex[2];
        Mxm::Vec3 ac = c.toVec3() - a.toVec3();
        Mxm::Vec3 abc = ab.cross(ac);

        Mxm::Vec3 abPerp = ab.cross(abc);
        if (abPerp.dot(ao) > 0.0f) {
            simplex = Simplex(a, b);
            direction = abPerp;

            return true;
        }

        Mxm::Vec3 acPerp = abc.cross(ac);
        if (acPerp.dot(ao) > 0.0f) {
            simplex = { a, c };
            direction = acPerp;

            return true;
        }
        
        if (abc.dot(ao) < 0.0f) {
            abc = -abc;
            simplex = { a, c, b };
        }
        direction = abc;

        return true;
    }
    else if (simplex.size() == 4) {
        const MinkowskiPoint& c = simplex[2];
        const MinkowskiPoint& d = simplex[3];

        Mxm::Vec3 ac = c.toVec3() - a.toVec3();
        Mxm::Vec3 ad = d.toVec3() - a.toVec3();

        Mxm::Vec3 abc = ab.cross(ac);
        if (abc.dot(ao) > 0.0f) {
            simplex = { a, b, c };
            direction = abc;

            return true;
        }
        
        Mxm::Vec3 adb = ad.cross(ab);
        if (adb.dot(ao) > 0.0f) {
            simplex = { a, d, b };
            direction = adb;

            return true;
        }

        Mxm::Vec3 acd = ac.cross(ad);
        if (acd.dot(ao) > 0.0f) {
            simplex = { a, c, d };
            direction = acd;

            return true;
        }

        return false;
    }

    return false;
}

std::pair<MinkowskiTriangle, float> CollisionSystem::findClosestFace(const Polytope& polytope) {
    float minDist = std::numeric_limits<float>::max();
    MinkowskiTriangle closestFace = polytope[0];

    for (const auto& face : polytope) {
        Mxm::Vec3 n = face.normal();
        float dist = n.dot(face[0]);

        // гарантирую положительную дистанцию
        if (dist < 0.0f) {
            dist = -dist;
        }

        if (dist < minDist) {
            minDist = dist;
            closestFace = face;
        }
    }

    return { closestFace, minDist };
}

void CollisionSystem::expandPolytope(Polytope& polytope, const MinkowskiPoint& newPoint) {
    FixedVector<Edge, 64> uniqueEdges;

    size_t i = 0;
    while (i < polytope.size()) {
        const MinkowskiPoint& v0 = polytope[i][0];
    
        if (polytope[i].normal().dot(newPoint.toVec3() - v0.toVec3()) > 0.0f) {
            std::array<Edge, 3> edges = {
                Edge{ polytope[i][0], polytope[i][1] },
                Edge{ polytope[i][1], polytope[i][2] },
                Edge{ polytope[i][2], polytope[i][0] }
            };
    
            for (const auto& e : edges) {
                auto rev = e.reversed();
                auto found = std::find(uniqueEdges.begin(), uniqueEdges.end(), rev);
    
                if (found != uniqueEdges.end()) {
                    size_t index = found - uniqueEdges.begin();
                    uniqueEdges.erase_unordered(index);
                }
                else {
                    uniqueEdges.push_back(e);
                }
            }
    
            polytope.erase_unordered(i); 
        }
        else {
            i++; 
        }
    }

    for (const auto& e : uniqueEdges) {
        polytope.push_back(MinkowskiTriangle(e.a, e.b, newPoint));
    }
}
std::pair<bool, Simplex> CollisionSystem::gjkCollision(const Collider* collider1, const Collider* collider2) {
    Mxm::Vec3 direction = Mxm::Vec3(1.0f, 1.0f, 1.0f);
    MinkowskiPoint support = minkowskiDifference(collider1, collider2, direction);

    Simplex simplex;
    simplex.push_front(support);

    direction = -support.toVec3();

    int iters = 0;
    while (iters < 32) {
        support = minkowskiDifference(collider1, collider2, direction);

        if (direction.dot(support) < 0.0f) {
            return { false, simplex };
        }

        simplex.push_front(support);
        if (!handleSimplex(simplex, direction)) {
            return { true, simplex };
        }

        iters++;
    }
    return { false, simplex };
}
CollisionResult CollisionSystem::epaAlgorithm(const Collider* collider1, const Collider* collider2, const Simplex& simplex) {
    Polytope polytope;

    polytope.push_back(MinkowskiTriangle(simplex[0], simplex[1], simplex[2]));
    polytope.push_back(MinkowskiTriangle(simplex[0], simplex[3], simplex[1]));
    polytope.push_back(MinkowskiTriangle(simplex[0], simplex[2], simplex[3]));
    polytope.push_back(MinkowskiTriangle(simplex[1], simplex[3], simplex[2]));

    for (int i = 0; i < 24; i++) {
        auto [closestFace, closestDist] = findClosestFace(polytope);
        MinkowskiPoint newPoint = minkowskiDifference(collider1, collider2, closestFace.normal());

        float newDist = closestFace.normal().dot(newPoint);
        if (newDist - closestDist < 0.01f) {
            Mxm::Vec3 origin = Mxm::Vec3(0.0f);
            Mxm::Vec3 projBaryOrigin = closestFace.getProjBaryCoords(origin);

            Mxm::Vec3 contactA = closestFace[0].a * projBaryOrigin.x + closestFace[1].a * projBaryOrigin.y + closestFace[2].a * projBaryOrigin.z;
            Mxm::Vec3 contactB = closestFace[0].b * projBaryOrigin.x + closestFace[1].b * projBaryOrigin.y + closestFace[2].b * projBaryOrigin.z;
            
            return CollisionResult{ closestFace.normal(), closestDist, contactA, contactB };
        }

        expandPolytope(polytope, newPoint);
    }
    
    auto [closestFace, closestDist] = findClosestFace(polytope);

    Mxm::Vec3 origin = Mxm::Vec3(0.0f);
    Mxm::Vec3 projBaryOrigin = closestFace.getProjBaryCoords(origin);

    Mxm::Vec3 contactA = closestFace[0].a * projBaryOrigin.x + closestFace[1].a * projBaryOrigin.y + closestFace[2].a * projBaryOrigin.z;
    Mxm::Vec3 contactB = closestFace[0].b * projBaryOrigin.x + closestFace[1].b * projBaryOrigin.y + closestFace[2].b * projBaryOrigin.z;
    
    return CollisionResult{ closestFace.normal(), closestDist, contactA, contactB };
}

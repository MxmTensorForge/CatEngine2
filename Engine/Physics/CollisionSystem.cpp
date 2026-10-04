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
Mxm::Vec3 CollisionSystem::minkowskiDifference(const Collider* collider1, const Collider* collider2, const Mxm::Vec3& dir) {
    return furthestPoint(collider1, dir) - furthestPoint(collider2, -dir);
}

bool CollisionSystem::handleSimplex(Simplex& simplex, Mxm::Vec3& direction) {
    Mxm::Vec3 a = simplex[0];
    Mxm::Vec3 b = simplex[1];
    Mxm::Vec3 ao = -a;
    Mxm::Vec3 ab = b - a;

    if (simplex.size() == 2) {
        direction = ab.cross(ao).cross(ab);

        return true;
    }
    else if (simplex.size() == 3) {
        Mxm::Vec3 c = simplex[2];
        Mxm::Vec3 ac = c - a;
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
        Mxm::Vec3 c = simplex[2];
        Mxm::Vec3 d = simplex[3];

        Mxm::Vec3 ac = c - a;
        Mxm::Vec3 ad = d - a;

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

std::pair<Triangle, float> CollisionSystem::findClosestFace(const Polytope& polytope) {
    float minDist = std::numeric_limits<float>::max();
    Triangle closestFace = polytope[0];

    for (const auto& face : polytope) {
        Mxm::Vec3 n = face.normal();
        float dist = n.dot(face[0].toVec3());

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

void CollisionSystem::expandPolytope(Polytope& polytope, const Mxm::Vec3& newPoint) {
    FixedVector<Edge, 64> uniqueEdges;

    size_t i = 0;
    while (i < polytope.size()) {
        Mxm::Vec3 v0 = polytope[i][0].toVec3();
    
        if (polytope[i].normal().dot(newPoint - v0) > 0.0f) {
            std::array<Edge, 3> edges = {
                Edge{ polytope[i][0].toVec3(), polytope[i][1].toVec3() },
                Edge{ polytope[i][1].toVec3(), polytope[i][2].toVec3() },
                Edge{ polytope[i][2].toVec3(), polytope[i][0].toVec3() }
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
        polytope.push_back(Triangle(e.a, e.b, newPoint));
    }
}
std::pair<bool, Simplex> CollisionSystem::gjkCollision(const Collider* collider1, const Collider* collider2) {
    Mxm::Vec3 direction = Mxm::Vec3(1.0f, 1.0f, 1.0f);
    Mxm::Vec3 support = minkowskiDifference(collider1, collider2, direction);

    Simplex simplex;
    simplex.push_front(support);

    direction = -support;

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

    polytope.push_back(Triangle(simplex[0], simplex[1], simplex[2]));
    polytope.push_back(Triangle(simplex[0], simplex[3], simplex[1]));
    polytope.push_back(Triangle(simplex[0], simplex[2], simplex[3]));
    polytope.push_back(Triangle(simplex[1], simplex[3], simplex[2]));

    for (int i = 0; i < 24; i++) {
        auto [closestFace, closestDist] = findClosestFace(polytope);
        Mxm::Vec3 newPoint = minkowskiDifference(collider1, collider2, closestFace.normal());

        float newDist = closestFace.normal().dot(newPoint);
        if (newDist - closestDist < 0.01f) {
            return CollisionResult{ closestFace.normal(), closestDist };
        }

        expandPolytope(polytope, newPoint);
    }
    
    auto [closestFace, closestDist] = findClosestFace(polytope);
    return CollisionResult{ closestFace.normal(), closestDist };
}

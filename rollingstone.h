#ifndef ROLLINGSTONE_H
#define ROLLINGSTONE_H

#include "octahedronball.h"
class Collision;
class TriangleSurface;
class RollingStone : public OctahedronBall {
public:
    RollingStone();

    void update();
    vec3 velocity() const;
    std::vector<vec3> currentTriangle{};

private:
    vec3 mVelocity{0};
    vec3 mAcceleration{0};
    vec3 lastAcceleration;

    vec3 gravity{0, -9.81f, 0};
    float mMass{1};

    double deltaTime{0.016f};

    Collision *collisionSystem;
    void calculateVelocity(vec3 normal, double distanceToTriangle);
};

#endif // ROLLINGSTONE_H

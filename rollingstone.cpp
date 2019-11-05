#include "rollingstone.h"
#include "collision.h"
#include "trianglesurface.h"

/**
 * @brief RollingStone::RollingStone constructor, creates a new collision system
 */
RollingStone::RollingStone() {
    collisionSystem = new Collision;
}

/**
 * @brief RollingStone::update
 * if we are on a triangle, calculate our normal and current distance to triangle
 * calculate the velocity
 */
void RollingStone::update() {
    if (!currentTriangle.empty()) {
        auto [normal, distance] = collisionSystem->getBallNormal(currentTriangle, *this); // c++17
        calculateVelocity(normal, distance);
    } else
        calculateVelocity(vec3(0), radius());
}

/**
* @brief RollingStone::velocity
* @return velocity
*/
vec3 RollingStone::velocity() const {
    return mVelocity;
}

/**
 * @brief RollingStone::calculateVelocity, calculates velocity of object
 * @param normal
 * @param distanceToTriangle
 */
void RollingStone::calculateVelocity(vec3 normal, double distanceToTriangle) {
    vec3 N = normal * vec3::dot(-gravity, normal);
    vec3 newPos = getPosition();
    // Bevegelsesligning hentet fra .pdf
    newPos += (velocity() * deltaTime) + (mAcceleration * 0.5 * pow(deltaTime, 2));
    move(newPos);

    // Newton's 2nd law
    vec3 force = gravity * mMass;

    // Liten og dårlig kollisjonssjekk
    if (distanceToTriangle <= radius()) {
        force = N + gravity;
    }

    // ny akselerasjon
    vec3 newAcceleration = force / mMass;
    // (initiell akselerasjon + ny akselerasjon) * 1/2t
    vec3 deltaV = (mAcceleration + newAcceleration) * (0.5 * deltaTime);
    deltaV = deltaV * 100;
    mVelocity = deltaV;
}

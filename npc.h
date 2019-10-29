#ifndef NPC_H
#define NPC_H

#include "visualobject.h"
#include "bsplinecurve.h"
#include "vector3d.h"
#include <queue>


typedef gsl::Vector3D vec3;
/**
 * @brief The NPC class
 */
enum NPCstates {PATROL, LEARN, SLEEP, CHASE};
enum NPCevents {ENDPOINT_ARRIVED, ITEM_TAKEN, OBSTACLE_DETECTED, PLAYER_DETECTED};
class NPC : public VisualObject
{
public:
    NPC(BSplineCurve& bsplinecurve);
    /* Litt kommentarer fra tavla ang. impementasjon
     * Implementere FSM:
     * NPC <-> Kontrollpkter(items, endepunkter)
     * Trenger bsplinecurve
     * Trenger player.position
    */

    // FSM PART
    void patrol();
    void learn();

    // OpenGL drawing stuff
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute = -1);


private:
    BSplineCurve& bSplineCurve;
    vec3 player;
    // FSM PART
    int state;
    void notify(int notification);
    std::queue<int> notification_queue;
};

#endif // NPC_H

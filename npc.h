#ifndef NPC_H
#define NPC_H

#include "visualobject.h"
#include "bsplinecurve.h"
#include "vector3d.h"
#include "vector2d.h"
#include <queue>


typedef gsl::Vector3D vec3;
typedef gsl::Vector2D vec2;
/**
 * @brief The NPC class
 */
enum NPCstates {PATROL, LEARN, SLEEP, CHASE};
enum NPCevents {ENDPOINT_ARRIVED, ITEM_TAKEN, OBSTACLE_DETECTED, PLAYER_DETECTED};
class NPC : public VisualObject
{
public:
    NPC();
    /* Litt kommentarer fra tavla ang. impementasjon
     * Implementere FSM:
     * NPC <-> Kontrollpkter(items, endepunkter)
     * Trenger bsplinecurve
     * Trenger player.position
    */

    // FSM PART
    void patrol();
    void chase();
    void learn();

    // OpenGL drawing stuff
    void initVertexBufferObjects();
    void draw(GLint positionAttribute, GLint colorAttribute, GLint textureAttribute = -1);

    vec2 deBoor(float x);
private:
  //  BSplineCurve& bSplineCurve;
    vec3 player;

    // FSM PART
    int state;
    void notify(int notification);
    std::queue<int> notification_queue;

    float elapsed_time;
    // B-spline kurven har en skjøtvektor, f.eks {0,0,0,1,2,3,3,3}
    // elapsed time er en parameter
    // 0 <= elapsed_time <= 3 i dette tilfellet
    void build_path();
    // Lag en ny bane for patrulering
    // gjøre en permutasjon av kontrollpunktene (kun items, ikke endepunkter)
    // viktig å ikke endre endepunktene
};

#endif // NPC_H

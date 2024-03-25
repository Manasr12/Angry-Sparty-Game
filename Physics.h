/**
 * @file Physics.h
 * @author Trey Cosnowski
 *
 * Physics class for a level
 */

#ifndef PROJECT_1_PHYSICS_H
#define PROJECT_1_PHYSICS_H
#include "box2d.h"

/**
 * Class for Physics
 */
class Physics {
private:
    /// The box2d world
    b2World mWorld;

    /// A ground reference object
    b2Body* mGround;

public:

    Physics(const b2Vec2& size);
    /// Default constructor (disabled)
    Physics() = delete;

    /// Copy constructor (disabled)
    Physics(const Physics &) = delete;

    /// Assignment operator
    void operator=(const Physics &) = delete;

    /**
     * Getter for mWorld
     * @return mWorld
     */

    b2World* GetWorld(){ return &mWorld; }
    b2World GetWorldDebug (){ return mWorld; }

    void Update(double frameRate);
    void DestroyBody(b2Body* body){mWorld.DestroyBody(body);}
};


#endif //PROJECT_1_PHYSICS_H

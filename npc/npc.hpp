#ifndef ENEMY_IS_INCLUDED
#define ENEMY_IS_INCLUDED

#include "moveable.hpp"
#include "mario.hpp"

class NPC : public Moveable
{
public:
    int status;
    NPC();
    NPC(float x, float y, float width, float height, int myId, float vx, float vy);
    virtual void Init() override;
    virtual void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    virtual void MoveByTime(double timeDiff) override;
    // This method is not mandatory, feel free to delete it.
    virtual void CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff);
};

#endif
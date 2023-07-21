#ifndef COIN_IS_INCLUDED
#define COIN_IS_INCLUDED

#include "base.hpp"
#include "npc.hpp"
#include "mario.hpp"
#include <cstdio>

class Coin : public NPC
{
public:
    const float RANGE = 2;
    const float VELOCITY = 10;
    float top;

    Coin();
    Coin(float x, float y, float width, float height);
    virtual void Init() override;
    virtual void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    virtual void MoveByTime(double timeDiff) override;
    virtual void ApplyRenderStatus() override;
};

#endif
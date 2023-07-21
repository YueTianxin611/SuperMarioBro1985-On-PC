#include "base.hpp"
#include "mario.hpp"
#include "npc.hpp"
#include <memory>
#include "npc.hpp"

class Goomba : public NPC
{
public:
    const float VX = 3;
    const float VY_DOWN = 10;
    int direction = -1; // -1: left, 1: right
    const double DISAPPEAR = 2;
    double clock;
    bool fall = true;

    Goomba(float x, float y, float width, float height);
    Goomba(float x, float y, float width, float height, int direction);
    virtual void Init() override;
    virtual void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    virtual void MoveByTime(double timeDiff) override;
    virtual void ApplyRenderStatus() override;
    virtual void CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff) override;
};
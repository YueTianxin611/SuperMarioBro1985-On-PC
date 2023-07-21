#include "base.hpp"
#include "npc.hpp"
#include "mario.hpp"

class Star : public NPC
{
public:
    const float VX = 3;
    const float VY_DOWN = 10;
    const float VY_UP = 5;
    const float UP = 1;
    float top;
    // SMBbase block;
    int direction = 1; // -1: left, 1: right
    bool fall = true;
    bool updateMario = false;

    Star(float x, float y, float width, float height);
    Star(float x, float y, float width, float height, int direction);
    virtual void Init() override;
    void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    virtual void MoveByTime(double timeDiff) override;
    virtual void ApplyRenderStatus() override;
    virtual void CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff) override;
};
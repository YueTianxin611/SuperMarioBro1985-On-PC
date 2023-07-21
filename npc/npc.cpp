#include "npc.hpp"
#include "base.hpp"
#include "moveable.hpp"

NPC::NPC()
{
}

NPC::NPC(float x, float y, float width, float height, int myId, float vx, float vy) : Moveable(x, y, width, height, 0.1, myId, vx, vy)
{
}

void NPC::Init()
{
}

void NPC::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
}

void NPC::MoveByTime(double timeDiff)
{
}

void NPC::CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff)
{
}

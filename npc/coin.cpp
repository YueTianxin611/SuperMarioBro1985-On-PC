#include "coin.hpp"

Coin::Coin()
{
    Coin::Init();
}


Coin::Coin(float x, float y, float width, float height) : NPC(x, y, width, height, SMBbase::objectId::COIN, 0, 0)
{
    this->status = 0;
    this->top = y + RANGE;
}

void Coin::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::COIN;
    this->status = 0; // 0: hidden by blocks, 1: up, 2: down, -1: disapper
    this->top = y + RANGE;
}

void Coin::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    if (status == -1)
    {
        SetCanCollide(false);
        return;
    }
    if (status == 0 && IsDownHit(collisionResult) && other.myId == SMBbase::objectId::MARIO)
    {
        status = 1;
    }
}

void Coin::MoveByTime(double timeDiff)
{
    if (status == 1)
    {
        y += timeDiff * VELOCITY;
        if (y >= top)
        {
            y = top;
            status = 2;
        }
    }
    else if (status == 2)
    {
        y -= timeDiff * VELOCITY;
        if (y <= top - RANGE)
        {
            status = -1;
        }
    }
    AddToTimer(timeDiff);
}

void Coin::ApplyRenderStatus()
{
    if (status == -1)
    {
        this->renderer.isVisible = false;
    }

    int renderstatus = int(timeSinceLastStatusChange / 0.1) % 4;
    switch (renderstatus)
    {
    case 0:
        this->renderer.SetRenderState(0);
        break;
    case 1:
        this->renderer.SetRenderState(1);
        break;
    case 2:
        this->renderer.SetRenderState(2);
        break;
    case 3:
        this->renderer.SetRenderState(3);
        break;
    }
}
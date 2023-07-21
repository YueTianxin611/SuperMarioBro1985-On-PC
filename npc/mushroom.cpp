#include "mushroom.hpp"

Mushroom::Mushroom(float x, float y, float width, float height) : NPC(x, y, width, height, SMBbase::objectId::MUSHROOM, 0, 0)
{
    status = 0;
    top = y + UP;
}

Mushroom::Mushroom(float x, float y, float width, float height, int direction) : NPC(x, y, width, height, SMBbase::objectId::MUSHROOM, 0, 0)
{
    this->direction = direction;
    status = 0;
    top = y + UP;
}

void Mushroom::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::MUSHROOM;
    this->status = 0; // 0: hidden by blocks, 1: normal move, 2: fall, 3: up, -1: diaspper
}

void Mushroom::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    if (y < 0)
    {
        status = -1;
    }
    if (status == -1)
    {
        SetCanCollide(false);
        return;
    }
    if ((status != 0 && status != -1) && !IsNoHit(collisionResult) && other.myId == SMBbase::objectId::MARIO)
    { // appear & hit by mario
        updateMario = true;
        status = -1;
        SetCanCollide(false);
        // may update mario to be undefeated
        return;
    }

    if (status == 0 && IsDownHit(collisionResult) && other.myId == SMBbase::objectId::MARIO)
    { // hidden then hit by mario
        status = 3;
        return;
    }
    if (status == 1 && other.myId == SMBbase::objectId::BLOCK)
    {
        if (IsLeftHit(collisionResult))
        {
            if (direction == -1)
            {
                x = other.x + other.width;
                direction = 1;
            }
        }
        else if (IsRightHit(collisionResult))
        {
            if (direction == 1)
            {
                x = other.x - width;
                direction = -1;
            }
        }
        else if (IsDownHit(collisionResult))
        {
            fall = false;
        }
    }
    if (status == 2)
    {
        if (IsDownHit(collisionResult) && other.myId == SMBbase::objectId::BLOCK)
        {
            status = 1;
            y = other.y + other.height;
            fall = false;
        }
    }
}

void Mushroom::MoveByTime(double timeDiff)
{
    if (status == 1 && fall)
    {
        status = 2;
    }
    if (status == 1)
    {
        x += timeDiff * VX * direction;
    }
    else if (status == 2)
    {
        x += timeDiff * VX * direction;
        y -= timeDiff * VY_DOWN;
    }
    else if (status == 3)
    {
        y += VY_UP * timeDiff;
        if (y >= top)
        {
            status = 1;
            y = top;
        }
    }
    fall = true;
    AddToTimer(timeDiff);
}

void Mushroom::ApplyRenderStatus()
{
    // 0: hidden by blocks, 1: normal move, 2: fall, 3: up, -1: diaspper
    if (status == -1)
    {
        this->renderer.isVisible = false;
    }
    if (direction == 1)
    {
        this->renderer.isFlip = false;
    }
    else
    {
        this->renderer.isFlip = true;
    }
    this->renderer.SetRenderState(0);
}

void Mushroom::CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff)
{
    if (updateMario)
    { // appear & hit by mario
        other.EatMushroom();
        printf("call mario eatmushroom with status %d\n", status);
        updateMario = false;
    }
}
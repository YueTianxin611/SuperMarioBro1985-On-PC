#include "goomba.hpp"

Goomba::Goomba(float x, float y, float width, float height) : NPC(x, y, width, height, SMBbase::objectId::GOOMBA, 0, 0)
{
    this->status = 1;
    clock = DISAPPEAR;
}
Goomba::Goomba(float x, float y, float width, float height, int direction) : NPC(x, y, width, height, SMBbase::objectId::GOOMBA, 0, 0)
{
    this->status = 1;
    this->direction = direction;
    clock = DISAPPEAR;
}

void Goomba::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::GOOMBA;
    this->status = 1; // 1: normal move, 2: normal_fall, 3: squeezed  4: upside down_fall, -1: diaspper
    clock = DISAPPEAR;
}

void Goomba::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    if (status == 1 && other.myId == SMBbase::objectId::MARIO)
    {
        auto mario = dynamic_cast<Mario *>(&other);
        if (mario->isImmortal && !IsNoHit(collisionResult))
        {
            status = 4;
            SetCanCollide(false);
        }
    }
    if (y < 0 || clock <= 0)
    {
        status = -1;
    }
    if (status == -1)
    {
        SetCanCollide(false);
        return;
    }

    if (status == 1)
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
        else if (IsDownHit(collisionResult && other.myId == SMBbase::objectId::BLOCK))
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
    if (status == 1 && IsUpHit(collisionResult) && other.myId == SMBbase::objectId::MARIO)
    {
        status = 3;
        this->SetCanCollide(false);
    }
    if (status == 3)
    {
        clock -= timeDiff;
        return;
    }
}

void Goomba::MoveByTime(double timeDiff)
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
    else if (status == 4)
    {
        y -= timeDiff * VY_DOWN;
    }
    AddToTimer(timeDiff);
    fall = true;
}

void Goomba::ApplyRenderStatus()
{
    // 1: normal move, 2: normal_fall, 3: squeezed  4: upside down_fall, -1: diaspper
    // currently we don't consider status = 4;
    // for status 1/2: goomba normal
    // for status 3: goomba die
    if (status == -1)
    {
        this->renderer.isVisible = false;
    }
    if (status == 1 || status == 2)
    {
        int renderstatus = int(timeSinceLastStatusChange / 0.1) % 2;
        if (renderstatus == 0)
        {
            this->renderer.isFlip = false;
        }
        else
        {
            this->renderer.isFlip = true;
        }
        this->renderer.SetRenderState(0);
    }
    else if (status == 3)
    {
        this->renderer.SetRenderState(1);
    }
    else if (status == 4)
    {
        this->renderer.SetRenderState(0);
        // TODO(Xin): update render state;
        this->renderer.SetRenderIsUpSideDown(true);
    }
}

void Goomba::CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff)
{
    return;
}
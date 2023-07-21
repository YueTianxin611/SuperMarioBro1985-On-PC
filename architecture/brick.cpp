#include "brick.hpp"

Brick::Brick()
{
    Brick::Init();
    this->vy = 0;
    this->origin_x_pos = 0;
    this->origin_y_pos = 0;
    this->max_height = origin_y_pos + MOVE_UP_DISTANCE;
    this->isQuestion = false;
}

void Brick::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::BLOCK;
}

Brick::Brick(float x, float y, float width, float height, float vx, float vy, bool isQ) : Moveable(x, y, width, height, 0.1, SMBbase::objectId::BLOCK, 0, 0)
// isQ: true if it's a question mark brick
{
    this->Y_VELOCITY = vy;
    this->origin_x_pos = x;
    this->origin_y_pos = y;
    this->max_height = origin_y_pos + MOVE_UP_DISTANCE;
    this->isQuestion = isQ;
    if (isQuestion)
    {
        brickState = brickState::WITHQUESTION;
    }
}

Brick::Brick(float x, float y, float width, float height, bool isQ) : Moveable(x, y, width, height, 0.1, SMBbase::objectId::BLOCK, 0, 0)
// isQ: true if it's a question mark brick
{
    this->Y_VELOCITY = 6;
    this->origin_x_pos = x;
    this->origin_y_pos = y;
    this->max_height = origin_y_pos + MOVE_UP_DISTANCE;
    this->isQuestion = isQ;
    if (isQuestion)
    {
        brickState = brickState::WITHQUESTION;
    }
}

void Brick::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    return;
}

void Brick::CollisionUpdateSelf(Mario &mario, char collisionResult, double timeDiff)
{
    if (IsDownHit(collisionResult))
    {
        if (!isQuestion)
        {
            inair = true;
            if (mario.currentSizeStatus == mario.marioSizeStatus::BIG)
            {
                brickState = brickState::DESTROYED;
                x = 0;
                y = 0;
                width = 0;
                height = 0;
            }
            else
            {
                brickState = brickState::NORMAL;
                vy = Y_VELOCITY;
            }
        }
        else if (isQuestion)
        {
            if (brickState == brickState::WITHQUESTION)
            {
                inair = true;
                brickState = brickState::SOLID;
            }
            else
            {
                inair = false;
                brickState = brickState::SOLID;
            }
        }
    }
    else
    {
        return;
    }
}

void Brick::CollisionUpdateMario(Mario &mario, char collisionResult, double timeDiff)
{
    return;
}

void Brick::MoveByTime(double timeDiff)
{

    if (inair)
    {
        this->y += vy * timeDiff;
        if (this->y >= max_height)
        {
            y = max_height;
            vy = -Y_VELOCITY;
        }
        else if (this->y <= origin_y_pos)
        {
            this->y = origin_y_pos;
            vy = 0;
            inair = false;
        }
    }
    AddToTimer(timeDiff);
}

void Brick::ApplyRenderStatus()
{
    if (brickState == brickState::WITHQUESTION)
    {
        int renderstatus = int(timeSinceLastStatusChange / 0.5) % 3;
        this->renderer.SetRenderState(renderstatus);
    }
    else if (brickState == brickState::DESTROYED)
    {
        this->renderer.isVisible = false;
    }
    else if (brickState == brickState::NORMAL)
    {
        this->renderer.SetRenderState(4);
    }
    else if (brickState == brickState::SOLID)
    {
        this->renderer.SetRenderState(3);
    }
}
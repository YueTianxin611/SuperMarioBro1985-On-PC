#include "mario.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Mario::Mario()
{
    Mario::Init();
}

void Mario::Init()
{
    Moveable::Init();
    this->myId = SMBbase::objectId::MARIO;
    SetBBX(5.0, 3.0, 1.0, 1.0);
    currentLocStatus = marioLocStatus::ON_GROUND;
    currentSizeStatus = marioSizeStatus::SMALL;
    currentCanDash = false;
    currentVxHasChanged = false;
    currentIsRunning = false;
    inSizeChange = false;
    inChangeTime = 0;
    isImmortal = false;
    immortalTime = 0;
    onGoomba = false;
    live = true;
    hitResultAccumulator = 0;
}

Mario::Mario(float x, float y, float width, float height,
             float bbxRatio, float vx, float vy)
{
    Moveable(x, y, width, height, bbxRatio, SMBbase::objectId::MARIO, vx, vy);
}

void Mario::AccRight(double timeDiff)
{
    if (!live)
        return;
    if (currentCanDash)
    {
        if (vx < MAX_DASHING_VX)
        {
            vx = std::min(MAX_DASHING_VX, vx + DASHING_ACC_X * float(timeDiff));
        }
    }
    else
    {
        if (vx < MAX_WALKING_VX)
        {
            vx = std::min(MAX_WALKING_VX, vx + WALKING_ACC_X * float(timeDiff));
        }
    }
    currentVxHasChanged = true;
}

void Mario::AccLeft(double timeDiff)
{
    if (!live)
        return;
    if (currentCanDash)
    {
        if (vx > -MAX_DASHING_VX)
        {
            vx = std::max(-MAX_DASHING_VX, vx - DASHING_ACC_X * float(timeDiff));
        }
    }
    else
    {
        if (vx > -MAX_WALKING_VX)
        {
            vx = std::max(-MAX_WALKING_VX, vx - WALKING_ACC_X * float(timeDiff));
        }
    }
    currentVxHasChanged = true;
}

void Mario::Jump(double timeDiff)
{
    if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
    {
        vy += JUMP_ACC_Y * float(timeDiff);
        y += 3 * EPSILON;
        currentLocStatus = Mario::marioLocStatus::ON_AIR;
        timeSinceLastStatusChange = 0;
    }
    else
    {
        if (timeSinceLastStatusChange < JUMP_TOLERANCE_SEC)
        {
            vy += JUMP_ACC_Y * float(timeDiff);
            vy = std::min(vy, MAX_VY);
        }
    }
}

void Mario::NoXInput(double timeDiff)
{
    if (vx > EPSILON)
    {
        vx = std::max(0.0f, vx - NO_INPUT_DEACC_X * float(timeDiff));
    }
    else if (vx < -EPSILON)
    {
        vx = std::min(0.0f, vx + NO_INPUT_DEACC_X * float(timeDiff));
    }
    else
    {
        vx = 0;
    }
}

void Mario::ApplyGravity(double timeDiff)
{
    vy -= GRAVITY * float(timeDiff);
    vy = std::max(vy, -MAX_VY);
    vy = std::min(vy, MAX_VY);
}

void Mario::MoveByTime(double timeDiff)
{
    if (inSizeChange)
    {
        vx = 0;
        vy = 0;
        inChangeTime += timeDiff;
        return;
    }
    if (!currentVxHasChanged)
    {
        NoXInput(timeDiff);
    }
    currentVxHasChanged = false;

    if (currentLocStatus == marioLocStatus::ON_AIR)
    {
        ApplyGravity(timeDiff);
    }
    x += vx * float(timeDiff);
    y += vy * float(timeDiff);
    AddToTimer(timeDiff);
    if (isImmortal)
    {
        immortalTime += timeDiff;
        if (immortalTime > 10.0)
        {
            isImmortal = false;
            immortalTime = 0;
        }
    }
}

void Mario::CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff)
{
    hitResultAccumulator |= collisionResult;
    if (inSizeChange)
    {
        vx = 0;
        vy = 0;
        return;
    }
    if (IsNoHit(collisionResult))
    {
        return;
    }

    switch (other.myId)
    {
    case SMBbase::objectId::BLOCK:

        if (IsUpHit(collisionResult))
        {
            y = other.y - height - EPSILON;
            if (vy > 0)
            {
                vy = 0;
            }
        }
        if (IsDownHit(collisionResult))
        {
            if (this->currentLocStatus == marioLocStatus::ON_GROUND)
            {
                if (this->currentIsRunning)
                {
                    if (vx < EPSILON && vx > -EPSILON)
                    {
                        this->currentIsRunning = false;
                        ClearTimer();
                    }
                }
                else
                {
                    if (vx > EPSILON || vx < -EPSILON)
                    {
                        this->currentIsRunning = true;
                        ClearTimer();
                    }
                }
            }
            else
            {
                this->currentLocStatus = marioLocStatus::ON_GROUND;
                vy = 0;
                y = other.y + other.height - EPSILON;
            }
        }
        if (IsRightHit(collisionResult))
        {
            // printf("Mario right hit\n");
            if (vx > 0)
            {
                vx = 0;
            }
        }
        if (IsLeftHit(collisionResult))
        {
            // printf("Mario left hit\n");
            if (vx < 0)
            {
                vx = 0;
            }
        }
        break;
    case SMBbase::objectId::COIN:
        // add scores
        break;
    case SMBbase::objectId::GOOMBA:
        if (IsNoHit(collisionResult))
        {
            return;
        }
        if (IsDownHit(collisionResult))
        {         
                vy *= -0.8;
                vx *= 0.2;
                onGoomba = true;
        }
        else if (!isImmortal)
        {
            if (currentSizeStatus == Mario::marioSizeStatus::BIG)
            {
                inSizeChange = true; // big to small
                SetCanCollide(false);
                inChangeTime = 0;
                vx = 0;
                vy = 0;
            }
            else
            {
                // lives--;
                live = false;
                vy = MAX_VY / 1.8;
                vx = 0;
                SetCanCollide(false);
            }
        }
        break;
    }
}

void Mario::CollisionCheckStart()
{
    hitResultAccumulator = 0;
}

void Mario::CollisionCheckEnd()
{
    if (!IsDownHit(hitResultAccumulator))
    {
        if (currentLocStatus != marioLocStatus::ON_AIR)
        {
            currentLocStatus = marioLocStatus::ON_AIR;
            ClearTimer();
        }
    }
}

void Mario::ApplyRenderStatus()
{
    if (!live)
    {
        renderer.SetRenderState(5); // SMALL_MARIO_GG
        return;
    }
    if (isImmortal)
    {
        float randR = (std::rand() % 256) / 255.0;
        float randG = (std::rand() % 256) / 255.0;
        float randB = (std::rand() % 256) / 255.0;
        renderer.SetRenderColor(randR, randG, randB, 1.0);
    }
    else
    {
        renderer.SetRenderColor(1.0, 1.0, 1.0, 1.0);
    }
    if (currentSizeStatus == Mario::marioSizeStatus::SMALL)
    {
        if (inSizeChange)
        {
            if (inChangeTime < SIZE_CHANGE_PERIOD * 0.7)
            {
                renderer.SetRenderState(7);
            }
            else if (inChangeTime < SIZE_CHANGE_PERIOD)
            { // 2 times render large
                renderer.SetRenderState(8);
            }
            else
            {
                inSizeChange = false;
                SetCanCollide(true);
                currentSizeStatus = Mario::marioSizeStatus::BIG;
                inChangeTime = 0;
            }
            return;
        }
        if (currentLocStatus == Mario::marioLocStatus::ON_AIR)
        {
            if (vx > 0)
            {
                renderer.SetRenderIsFlip(false);
            }
            else
            {
                renderer.SetRenderIsFlip(true);
            }
            if (onGoomba)
            {
                renderer.SetRenderState(3);
            }
            else
            {
                renderer.SetRenderState(4);
            }
        }
        else if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
        {
            onGoomba = false;
            // decide direction
            if (vx > EPSILON)
            {
                renderer.SetRenderIsFlip(false);
            }
            else if (vx < -EPSILON)
            {
                renderer.SetRenderIsFlip(true);
            }
            // decide running
            if (!currentIsRunning)
            {
                renderer.SetRenderState(0);
            }
            else
            {
                int runningState = int(timeSinceLastStatusChange / RUNNING_ANIMATION_PERIOD) % 3;
                switch (runningState)
                {
                case 0:
                    renderer.SetRenderState(1);
                    break;
                case 1:
                    renderer.SetRenderState(2);
                    break;
                case 2:
                    renderer.SetRenderState(3);
                    break;
                }
            }
        }
        else
        {
            renderer.SetRenderState(0);
        }
    }
    else if (currentSizeStatus == Mario::marioSizeStatus::BIG)
    {
        if (inSizeChange)
        {
            if (inChangeTime < SIZE_CHANGE_PERIOD * 0.7)
            { // 3 times render middle
                renderer.SetRenderState(7);
            }
            else if (inChangeTime < SIZE_CHANGE_PERIOD)
            { // 2 times render small
                renderer.SetRenderState(0);
                height = 1.0;
            }
            else
            {
                inSizeChange = false;
                SetCanCollide(true);
                currentSizeStatus = Mario::marioSizeStatus::SMALL;
                inChangeTime = 0;
            }
            return;
        }
        if (currentLocStatus == Mario::marioLocStatus::ON_AIR)
        {
            if (vx > 0)
            {
                renderer.SetRenderIsFlip(false);
            }
            else
            {
                renderer.SetRenderIsFlip(true);
            }
            if (onGoomba)
            {
                renderer.SetRenderState(3);
            }
            else
            {
                renderer.SetRenderState(12); // LARGE_MARIO_JUMP
            }
        }
        else if (currentLocStatus == Mario::marioLocStatus::ON_GROUND)
        {
            onGoomba = false;
            // decide direction
            if (vx > EPSILON)
            {
                renderer.SetRenderIsFlip(false);
            }
            else if (vx < -EPSILON)
            {
                renderer.SetRenderIsFlip(true);
            }
            // decide running
            if (!currentIsRunning)
            {
                renderer.SetRenderState(8); // LARGE_MARIO_STAND
            }
            else
            {
                int runningState = int(timeSinceLastStatusChange / RUNNING_ANIMATION_PERIOD) % 3;
                switch (runningState)
                {
                case 0:
                    renderer.SetRenderState(9); // LARGE_MARIO_WALK_0
                    break;
                case 1:
                    renderer.SetRenderState(10); // LARGE_MARIO_WALK_1
                    break;
                case 2:
                    renderer.SetRenderState(11); // LARGE_MARIO_WALK_2
                    break;
                }
            }
        }
        else
        {
            renderer.SetRenderState(8); // LARGE_MARIO_STAND
        }
    }
}

bool Mario::EatMushroom()
{
    if (currentSizeStatus == Mario::marioSizeStatus::BIG || inSizeChange)
    {
        return false;
    }
    inSizeChange = true;
    SetCanCollide(false);
    inChangeTime = 0;
    vx = 0;
    vy = 0;
    height = 2.0;
    return true;
}

bool Mario::EatStar()
{
    isImmortal = true;
    immortalTime = 0;
    return true;
}
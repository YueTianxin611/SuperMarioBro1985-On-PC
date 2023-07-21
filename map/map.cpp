#include "map.hpp"
#include "base.hpp"
#include "coin.hpp"
#include "brick.hpp"
#include <memory>

Map::Map()
{
    Init();
}

void Map::Init()
{
    this->mario.Init();
    this->viewPortX = 0.0f;
    this->viewPortY = 0.0f;
    this->viewPortHeight = 15.0f;
    this->viewPortWidth = 15.0f;
    this->maxWorldX = 211.0f; // 3376 / 16
    this->maxWorldY = 15.0f;
}

float Map::GetVpHeight() const
{
    return viewPortHeight;
}

float Map::GetVpWidth() const
{
    return viewPortWidth;
}

float Map::GetVpX() const
{
    return viewPortX;
}

float Map::GetVpY() const
{
    return viewPortY;
}

float Map::GetMaxWorldX() const
{
    return maxWorldX;
}

float Map::GetMaxWorldY() const
{
    return maxWorldY;
}

void Map::UpdateViewPortWithMario()
{
    // teleported to underground
    if (mario.y < -2)
    {
        return;
    }
    float marioPropotion = (mario.x - viewPortX) / viewPortWidth;
    if (marioPropotion > VIEWPORT_MAX_RATIO)
    {
        viewPortX = mario.x - viewPortWidth * VIEWPORT_MAX_RATIO;
    }
    if (viewPortX >= maxWorldX - viewPortWidth)
    {
        viewPortX = maxWorldX - viewPortWidth;
    }
}

bool Map::IsInViewPort(SMBbase &obj) const
{
    float leftView = viewPortX;
    float rightView = viewPortX + viewPortWidth;
    float topView = viewPortY + viewPortHeight;
    float bottomView = viewPortY;

    float leftObj = obj.x;
    float rightObj = obj.x + obj.width;
    float topObj = obj.y + obj.height;
    float bottomObj = obj.y;

    if (leftObj > rightView || rightObj < leftView || topObj < bottomView || bottomObj > topView)
    {
        return false;
    }
    return true;
}

void Map::RestrictMarioX()
{   
    
    if (mario.y > 0 && mario.x < viewPortX)
    {
        mario.x = viewPortX;
        mario.vx = mario.vx < 0 ? -mario.EPSILON : mario.EPSILON;
    }
    if (mario.y > 0 && mario.x + mario.width >= maxWorldX)
    {
        mario.x = maxWorldX - mario.width;
        mario.vx = mario.vx < 0 ? -mario.EPSILON : mario.EPSILON;
    }
}

void Map::Collide(double timeDiff)
{
    // populate NPCs
    npcInViewPort.clear();
    for (auto &coin : coins)
    {
        if (IsInViewPort(coin))
        {
            npcInViewPort.push_back(&coin);
        }
    }
    for (auto &star : stars)
    {
        if (IsInViewPort(star))
        {
            npcInViewPort.push_back(&star);
        }
    }
    for (auto &mushroom : mushrooms)
    {
        if (IsInViewPort(mushroom))
        {
            npcInViewPort.push_back(&mushroom);
        }
    }
    for (auto &goomba : goombas)
    {
        if (IsInViewPort(goomba))
        {
            npcInViewPort.push_back(&goomba);
        }
    }
    // populate blocks
    blockInViewPort.clear();
    for (auto &b : blocks)
    {
        if (IsInViewPort(b))
        {
            blockInViewPort.push_back(&b);
        }
    }
    // populate moveable bricks
    brickInViewPort.clear();
    for (auto &b : bricks)
    {
        if (IsInViewPort(b))
        {
            brickInViewPort.push_back(&b);
        }
    }

    mario.CollisionCheckStart();
    for (auto npc : npcInViewPort)
    {
        auto res = mario.CheckCollision(*npc); // mario - npc
        mario.CollisionUpdateSelf(*npc, res, timeDiff);
        npc->CollisionUpdateMario(mario, res, timeDiff);
        npc->CollisionUpdateSelf(mario, npc->InverseCollision(res), timeDiff);
    }
    for (auto block : blockInViewPort)
    {
        auto res = mario.CheckCollision(*block); // mario - block
        mario.CollisionUpdateSelf(*block, res, timeDiff);
    }
    for (auto brick : brickInViewPort)
    {
        auto res = mario.CheckCollision(*brick);
        mario.CollisionUpdateSelf(*brick, res, timeDiff);
        brick->CollisionUpdateSelf(mario, brick->InverseCollision(res), timeDiff);
    }
    // check win
    auto res = mario.CheckCollision(winblock);
    if (!isWin && !mario.IsNoHit(res))
    {
        printf("YOU WIN\n");
        isWin = true;
    }
    // check teleport
    for (auto &t : teleports)
    {
        auto res = mario.CheckCollision(t);
        if (!mario.IsNoHit(res) && t.status == Teleport::teleportStatus::ACTIVATE)
        {
            t.Transport(mario);
            this->viewPortX = t.destViewPortX;
            this->viewPortY = t.destViewPortY;
            this->viewPortHeight = t.destViewPortHeight;
            this->viewPortWidth = t.destViewPortWidth;
            printf("teleport!\n");
            break;
        }
    }

    mario.CollisionCheckEnd();
    for (auto npc : npcInViewPort)
    {
        for (auto block : blockInViewPort)
        {
            auto npc_res = npc->CheckCollision(*block); // npc - block
            npc->CollisionUpdateSelf(*block, npc_res, timeDiff);
        }
        for (auto brick : brickInViewPort)
        {
            auto npc_res = npc->CheckCollision(*brick);
            npc->CollisionUpdateSelf(*brick, npc_res, timeDiff);
        }
    }
}

void Map::RefreshRenderState()
{
    mario.ApplyRenderStatus();
    for (auto n : npcInViewPort)
    {
        n->ApplyRenderStatus();
    }
    for (auto b : brickInViewPort)
    {
        b->ApplyRenderStatus();
    }
}

void Map::MoveOneStep(double timeDiff)
{
    mario.MoveByTime(timeDiff);
    for (auto n : npcInViewPort)
    {
        n->MoveByTime(timeDiff);
    }
    for (auto b : brickInViewPort)
    {
        b->MoveByTime(timeDiff);
    }
}

void Map::RunOneStep(double timeDiff)
{
    if (isWin)
    {
        return;
    }
    Collide(timeDiff);
    MoveOneStep(timeDiff);
    RefreshRenderState();
    UpdateViewPortWithMario();
    RestrictMarioX();
}
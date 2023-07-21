#ifndef MAP_IS_INCLUDED
#define MAP_IS_INCLUDED

#include <memory>
#include <vector>
#include "base.hpp"
#include "mario.hpp"
#include "npc.hpp"
#include "coin.hpp"
#include "mushroom.hpp"
#include "star.hpp"
#include "goomba.hpp"
#include "brick.hpp"
#include "teleport.hpp"

class Map
{
public:
    std::vector<SMBbase> blocks; // all the blocks that couldnot move
    // npcs
    std::vector<Coin> coins;
    std::vector<Mushroom> mushrooms;
    std::vector<Star> stars;
    std::vector<Goomba> goombas;
    // movable bricks
    std::vector<Brick> bricks;
    // in viewport
    std::vector<SMBbase *> blockInViewPort;
    std::vector<NPC *> npcInViewPort;
    std::vector<Brick *> brickInViewPort;

    SMBbase winblock;

    Mario mario;

    std::vector<SMBbase> undergrounds; // undergrounds
    std::vector<Teleport> teleports;
    float viewPortHeight, viewPortWidth;
    float viewPortX, viewPortY; // left bottom corner
    float maxWorldX, maxWorldY;
    bool isWin = false;
    const float VIEWPORT_MAX_RATIO = 0.6f;

    Map();

    float GetVpHeight() const;
    float GetVpWidth() const;
    float GetVpX() const;
    float GetVpY() const;
    float GetMaxWorldX() const;
    float GetMaxWorldY() const;

    void Init();
    void UpdateViewPortWithMario();
    bool IsInViewPort(SMBbase &obj) const;
    void RestrictMarioX();
    void RefreshRenderState();

    void Collide(double timeDiff);
    void MoveOneStep(double timeDiff);
    void RunOneStep(double timeDiff);
};

#endif
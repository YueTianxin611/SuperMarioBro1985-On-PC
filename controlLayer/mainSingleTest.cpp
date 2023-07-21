#include "controller.hpp"
#include <chrono>
#include "fssimplewindow.h"

void Init(Controller &c)
{
    // mario
    c.map.mario.SetBBX(5, 2, 1, 1);
    // unmoveable blocks
    c.map.blocks.clear();
    c.map.blocks.push_back(SMBbase(0, 0, 15, 2, 0.1, SMBbase::objectId::BLOCK));
    // NPCs
    c.map.coins.clear();
    c.map.coins.push_back(Coin(8, 4, 1, 1));
    // Stars
    c.map.stars.clear();
    c.map.stars.push_back(Star(5, 4, 1, 1));
    // Mushrooms
    c.map.mushrooms.clear();
    c.map.mushrooms.push_back(Mushroom(6, 4, 1, 1));
    // Goombas
    c.map.goombas.clear();
    c.map.goombas.push_back(Goomba(10, 2, 1, 1, -1));
    // Bricks
    c.map.bricks.clear();
    c.map.bricks.push_back(Brick(1, 4, 1, 1, true));
    c.map.bricks.push_back(Brick(2.5, 4, 1, 1, false));
    c.map.bricks.push_back(Brick(6, 4, 1, 1, true));
    c.map.bricks.push_back(Brick(5, 4, 1, 1, true));
}

int main()
{
    FsChangeToProgramDir();
    FsOpenWindow(32, 32, 600, 600, 1);
    Controller c;
    Init(c);
    c.InitTexture();
    auto now = std::chrono::system_clock::now();
    double time_interval = 0;
    while (true != c.IsTerminated())
    {
        FsGetWindowSize(c.screenWidth, c.screenHeight);
        auto next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000.0;
        now = next_now;

        c.RunOneStep(time_interval);
        c.Draw();
        // break;
        FsSleep(10);
    }
}
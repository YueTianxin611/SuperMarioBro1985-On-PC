#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "controller.hpp"
#include "base.hpp"
#include "coin.hpp"
#include "textureRegister.h"
#include "npc.hpp"
#include "mario.hpp"
#include "brick.hpp"
#include "teleport.hpp"
#include <cstdlib>

Controller::Controller()
{
    this->Init();
}

Controller::~Controller()
{
}

void Controller::Init()
{
    screenWidth = 480;
    screenHeight = 480;
}

void Controller::InitTexture()
{ // 1 means 1 texture file
    td.resize(2);
    // must use absolute path and I don't know why
    int res = td.decoders[0].Decode("world1-1.png");
    if (YSERR == res)
    {
        printf("======\ndecode map failed\n======\n");
    }
    else
    {
        printf("======\ndecode map success\n======\n");
        printf("======\nmap size: %d, %d\n======\n", td.decoders[0].wid, td.decoders[0].hei);
    }

    res = td.decoders[1].Decode("tileset.png");
    if (YSERR == res)
    {
        printf("======\ndecode tileset failed\n======\n");
    }
    else
    {
        printf("======\ndecode tileset success\n======\n");
    }
    // color means the background color. using white here
    float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    td.setRGBA(color);

    // register texture to opengl.
    // using for loop since might have multiple textures.
    int rgba_idx = 0;
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < td.size; ++i)
    {
        rgba_idx = i * 4;
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(td.rgba[rgba_idx],
                  td.rgba[rgba_idx + 1],
                  td.rgba[rgba_idx + 2],
                  td.rgba[rgba_idx + 3]);
        glGenTextures(1, &td.texIds[i]);
        glBindTexture(GL_TEXTURE_2D, td.texIds[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     td.decoders[i].wid,
                     td.decoders[i].hei,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     td.decoders[i].rgba);
    }

    // init background renderer
    bgRenderer.SetTextureId(0); // first texture
    // init mario renderer
    TextureRegister tr;
    map.mario.renderer.AddRenderState(0, TextureCoord(tr.SMALL_MARIO_STAND));
    map.mario.renderer.AddRenderState(1, TextureCoord(tr.SMALL_MARIO_WALK_0));
    map.mario.renderer.AddRenderState(2, TextureCoord(tr.SMALL_MARIO_WALK_1));
    map.mario.renderer.AddRenderState(3, TextureCoord(tr.SMALL_MARIO_WALK_2));
    map.mario.renderer.AddRenderState(4, TextureCoord(tr.SMALL_MARIO_JUMP));
    map.mario.renderer.AddRenderState(5, TextureCoord(tr.SMALL_MARIO_GG));
    map.mario.renderer.AddRenderState(6, TextureCoord(tr.SMALL_MARIO_FLAG));
    map.mario.renderer.AddRenderState(7, TextureCoord(tr.SMALL_LARGE_MARIO));
    map.mario.renderer.AddRenderState(8, TextureCoord(tr.LARGE_MARIO_STAND));
    map.mario.renderer.AddRenderState(9, TextureCoord(tr.LARGE_MARIO_WALK_0));
    map.mario.renderer.AddRenderState(10, TextureCoord(tr.LARGE_MARIO_WALK_1));
    map.mario.renderer.AddRenderState(11, TextureCoord(tr.LARGE_MARIO_WALK_2));
    map.mario.renderer.AddRenderState(12, TextureCoord(tr.LARGE_MARIO_JUMP));
    map.mario.renderer.AddRenderState(13, TextureCoord(tr.LARGE_MARIO_GG));
    map.mario.renderer.AddRenderState(14, TextureCoord(tr.LARGE_MARIO_FLAG));
    map.mario.renderer.SetRenderState(0);
    map.mario.renderer.SetRenderTextureId(1); // second texture
    map.mario.renderer.SetRenderColor(1, 1, 1, 1);

    // init bricks renderer
    for (SMBbase &b : map.bricks)
    {
        b.renderer.AddRenderState(0, TextureCoord(tr.QUESTION_BLOCK_Q_0));
        b.renderer.AddRenderState(1, TextureCoord(tr.QUESTION_BLOCK_Q_1));
        b.renderer.AddRenderState(2, TextureCoord(tr.QUESTION_BLOCK_Q_2));
        b.renderer.AddRenderState(3, TextureCoord(tr.QUESTION_BLOCK_SOLID));
        b.renderer.AddRenderState(4, TextureCoord(tr.BREAKABLE_BLOCK));
        b.renderer.SetRenderState(0);
        b.renderer.SetRenderTextureId(1);
        b.renderer.SetRenderColor(1, 1, 1, 1);
    }

    // init coins renderer
    for (auto &c : map.coins)
    {
        c.renderer.AddRenderState(0, TextureCoord(tr.COIN_0));
        c.renderer.AddRenderState(1, TextureCoord(tr.COIN_1));
        c.renderer.AddRenderState(2, TextureCoord(tr.COIN_2));
        c.renderer.AddRenderState(3, TextureCoord(tr.COIN_3));
        c.renderer.SetRenderState(0);
        c.renderer.SetRenderTextureId(1);
        c.renderer.SetRenderColor(1, 1, 1, 1);
    }

    // init stars renderer
    for (auto &s : map.stars)
    {
        s.renderer.AddRenderState(0, TextureCoord(tr.STAR_0));
        s.renderer.AddRenderState(1, TextureCoord(tr.STAR_1));
        s.renderer.AddRenderState(2, TextureCoord(tr.STAR_2));
        s.renderer.AddRenderState(3, TextureCoord(tr.STAR_3));
        s.renderer.SetRenderState(0);
        s.renderer.SetRenderTextureId(1);
        s.renderer.SetRenderColor(1, 1, 1, 1);
    }
    // init mushrooms renderer
    for (auto &m : map.mushrooms)
    {
        m.renderer.AddRenderState(0, TextureCoord(tr.RED_MUSHROOM));
        m.renderer.SetRenderState(0);
        m.renderer.SetRenderTextureId(1);
        m.renderer.SetRenderColor(1, 1, 1, 1);
    }

    // init goombas renderer
    for (auto &g : map.goombas)
    {
        g.renderer.AddRenderState(0, TextureCoord(tr.GOOMBA_NORMAL));
        g.renderer.AddRenderState(1, TextureCoord(tr.GOOMBA_DIE));
        g.renderer.SetRenderState(0);
        g.renderer.SetRenderTextureId(1);
        g.renderer.SetRenderColor(1, 1, 1, 1);
    }
}

bool Controller::IsTerminated(void) const
{
    return term;
}

void Controller::RunOneStep(double timeDiff)
{
    FsPollDevice();
    if (FsGetKeyState(FSKEY_ESC))
    {
        term = true;
    }

    if (FsGetKeyState(FSKEY_LEFT))
    {
        map.mario.AccLeft(timeDiff);
    }
    if (FsGetKeyState(FSKEY_RIGHT))
    {
        map.mario.AccRight(timeDiff);
    }
    if (FsGetKeyState(FSKEY_UP))
    {
        map.mario.Jump(timeDiff);
    }
    else if (FsGetKeyState(FSKEY_SPACE))
    {
        map.mario.Jump(timeDiff);
    }

    if (FsGetKeyState(FSKEY_SHIFT))
    {
        map.mario.currentCanDash = true;
    }
    else
    {
        map.mario.currentCanDash = false;
    }

    if (FsGetKeyState(FSKEY_DOWN))
    {
        for (auto &t : map.teleports)
        {
            t.SetStatus(Teleport::teleportStatus::ACTIVATE);
        }
    }
    else
    {
        for (auto &t : map.teleports)
        {
            t.SetStatus(Teleport::teleportStatus::DEACTIVATE);
        }
    }

    if (FsGetKeyState(FSKEY_B))
    {
        map.mario.currentSizeStatus = map.mario.marioSizeStatus::BIG;
    }
    timePassed += timeDiff;
    map.RunOneStep(timeDiff);

    if (map.mario.y < -15)
    {
        printf("Game Over\n");
        InitWorld11();
    }
}

void Controller::ToScreenCoord(float &xmin, float &ymin, float &xmax, float &ymax, float x, float y, float w, float h) const
{
    xmin = W2VXRatio(x) * screenWidth;
    ymin = W2VYRatio(y + h) * screenHeight;
    xmax = W2VXRatio(x + w) * screenWidth;
    ymax = W2VYRatio(y) * screenHeight;
}

void Controller::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw background
    DrawBackground();
    // mario
    float xmin, ymin, xmax, ymax;
    ToScreenCoord(xmin, ymin, xmax, ymax, map.mario.x, map.mario.y, map.mario.width, map.mario.height);
    map.mario.renderer.Draw(td, xmin, ymin, xmax, ymax);
    // draw npcs:
    for (NPC *npc : map.npcInViewPort)
    {
        ToScreenCoord(xmin, ymin, xmax, ymax, npc->x, npc->y, npc->width, npc->height);
        npc->renderer.Draw(td, xmin, ymin, xmax, ymax);
    }
    // draw bricks
    for (Brick *brick : map.brickInViewPort)
    {
        ToScreenCoord(xmin, ymin, xmax, ymax, brick->x, brick->y, brick->width, brick->height);
        brick->renderer.Draw(td, xmin, ymin, xmax, ymax);
    }


    if (map.isWin)
    {
        DrawWin();
    }
    glDisable(GL_BLEND);
    FsSwapBuffers();
}

void Controller::DrawBackground()
{
    float xminPropW, yminPropW, xmaxPropW, ymaxPropW;
    xminPropW = map.GetVpX() / map.GetMaxWorldX();
    yminPropW = map.GetVpY() / map.GetMaxWorldY();
    xmaxPropW = (map.GetVpX() + map.GetVpWidth()) / map.GetMaxWorldX();
    ymaxPropW = (map.GetVpY() + map.GetMaxWorldY()) / map.GetMaxWorldY();
    float xminProp, yminProp, xmaxProp, ymaxProp;
    xminProp = xminPropW;
    xmaxProp = xmaxPropW;
    yminProp = (1 - ymaxPropW) / 2;
    ymaxProp = (1 - yminPropW) / 2;
    bgRenderer.SetProp(xminProp, yminProp, xmaxProp, ymaxProp);
    bgRenderer.Draw(td, screenWidth, screenHeight);
}

void Controller::DrawWin()
{
    float randR = (std::rand() % 256) / 255.0;
    float randG = (std::rand() % 256) / 255.0;
    float randB = (std::rand() % 256) / 255.0;
    glColor4f(randR, randG, randB, 1);
    glRasterPos2d(screenWidth / 2 - 3 * 32, screenHeight / 2 - 24);
    YsGlDrawFontBitmap32x48("You Win!");
}

float Controller::W2VXRatio(float worldx) const
{
    return (worldx - map.GetVpX()) / map.GetVpWidth();
}

float Controller::W2VYRatio(float worldy) const
{
    return 1 - ((worldy - map.GetVpY()) / map.GetVpHeight());
}

void Controller::SetScreenSize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
}

void Controller::InitWorld11()
{
    map.maxWorldX = 211;
    map.maxWorldY = 15;
    map.viewPortHeight = 15;
    map.viewPortWidth = 16;
    map.viewPortX = 0;
    map.viewPortY = 0;
    float bbxr = 0.1;
    // unmovable blocks
    map.blocks.clear();
    // grounds
    map.blocks.push_back(SMBbase(0, 0, 69, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(71, 0, 15, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(89, 0, 64, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(155, 0, 56, 2, bbxr, SMBbase::objectId::BLOCK));
    // pipes
    map.blocks.push_back(SMBbase(28, 2, 2, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(38, 2, 2, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(46, 2, 2, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(57, 2, 2, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(163, 2, 2, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(179, 2, 2, 2, bbxr, SMBbase::objectId::BLOCK));
    // unbreakable blocks
    map.blocks.push_back(SMBbase(134, 2, 1, 1, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(135, 2, 1, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(136, 2, 1, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(137, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));

    map.blocks.push_back(SMBbase(140, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(141, 2, 1, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(142, 2, 1, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(143, 2, 1, 1, bbxr, SMBbase::objectId::BLOCK));

    map.blocks.push_back(SMBbase(148, 2, 1, 1, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(149, 2, 1, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(150, 2, 1, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(151, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(152, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));

    map.blocks.push_back(SMBbase(155, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(156, 2, 1, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(157, 2, 1, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(158, 2, 1, 1, bbxr, SMBbase::objectId::BLOCK));

    map.blocks.push_back(SMBbase(181, 2, 1, 1, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(182, 2, 1, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(183, 2, 1, 3, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(184, 2, 1, 4, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(185, 2, 1, 5, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(186, 2, 1, 6, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(187, 2, 1, 7, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(188, 2, 1, 8, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(189, 2, 1, 8, bbxr, SMBbase::objectId::BLOCK));

    // mario
    map.mario.Init();
    map.mario.SetBBX(5, 3, 1, 1);

    // goombas
    map.goombas.clear();
    map.goombas.push_back(Goomba(22, 2, 1, 1));
    map.goombas.push_back(Goomba(41, 2, 1, 1));
    map.goombas.push_back(Goomba(50, 2, 1, 1));
    map.goombas.push_back(Goomba(52, 2, 1, 1));
    map.goombas.push_back(Goomba(80, 10, 1, 1));
    map.goombas.push_back(Goomba(82, 10, 1, 1));
    map.goombas.push_back(Goomba(97, 2, 1, 1));
    map.goombas.push_back(Goomba(99, 2, 1, 1));
    map.goombas.push_back(Goomba(113, 2, 1, 1));
    map.goombas.push_back(Goomba(115, 2, 1, 1));
    map.goombas.push_back(Goomba(123, 2, 1, 1));
    map.goombas.push_back(Goomba(125, 2, 1, 1));
    map.goombas.push_back(Goomba(128, 2, 1, 1));
    map.goombas.push_back(Goomba(130, 2, 1, 1));
    map.goombas.push_back(Goomba(174, 2, 1, 1));
    map.goombas.push_back(Goomba(176, 2, 1, 1));

    // mushrooms
    map.mushrooms.clear();
    map.mushrooms.push_back(Mushroom(21, 5, 1, 1));
    map.mushrooms.push_back(Mushroom(78, 5, 1, 1));
    map.mushrooms.push_back(Mushroom(109, 9, 1, 1));

    // stars
    map.stars.clear();
    map.stars.push_back(Star(101, 5, 1, 1));

    // coins
    map.coins.clear();
    map.coins.push_back(Coin(16, 5, 1, 1));
    map.coins.push_back(Coin(22, 9, 1, 1));
    map.coins.push_back(Coin(23, 5, 1, 1));
    map.coins.push_back(Coin(94, 5, 1, 1)); // hidden by a normal block
    map.coins.push_back(Coin(94, 9, 1, 1));
    map.coins.push_back(Coin(106, 5, 1, 1));
    map.coins.push_back(Coin(109, 5, 1, 1));
    map.coins.push_back(Coin(112, 5, 1, 1));
    map.coins.push_back(Coin(129, 9, 1, 1));
    map.coins.push_back(Coin(130, 9, 1, 1));
    map.coins.push_back(Coin(170, 5, 1, 1));

    // bricks
    map.bricks.clear();
    // question bricks
    map.bricks.push_back(Brick(16, 5, 1, 1, true));
    map.bricks.push_back(Brick(21, 5, 1, 1, true));
    map.bricks.push_back(Brick(22, 9, 1, 1, true));
    map.bricks.push_back(Brick(23, 5, 1, 1, true));
    map.bricks.push_back(Brick(78, 5, 1, 1, true));
    map.bricks.push_back(Brick(94, 9, 1, 1, true));
    map.bricks.push_back(Brick(106, 5, 1, 1, true));
    map.bricks.push_back(Brick(109, 5, 1, 1, true));
    map.bricks.push_back(Brick(109, 9, 1, 1, true));
    map.bricks.push_back(Brick(112, 5, 1, 1, true));
    map.bricks.push_back(Brick(129, 9, 1, 1, true));
    map.bricks.push_back(Brick(130, 9, 1, 1, true));
    map.bricks.push_back(Brick(170, 5, 1, 1, true));
    // normal bricks
    map.bricks.push_back(Brick(20, 5, 1, 1, false));
    map.bricks.push_back(Brick(22, 5, 1, 1, false));
    map.bricks.push_back(Brick(24, 5, 1, 1, false));
    map.bricks.push_back(Brick(77, 5, 1, 1, false));
    map.bricks.push_back(Brick(79, 5, 1, 1, false));

    map.bricks.push_back(Brick(80, 9, 1, 1, false));
    map.bricks.push_back(Brick(81, 9, 1, 1, false));
    map.bricks.push_back(Brick(82, 9, 1, 1, false));
    map.bricks.push_back(Brick(83, 9, 1, 1, false));
    map.bricks.push_back(Brick(84, 9, 1, 1, false));
    map.bricks.push_back(Brick(85, 9, 1, 1, false));
    map.bricks.push_back(Brick(86, 9, 1, 1, false));
    map.bricks.push_back(Brick(87, 9, 1, 1, false));

    map.bricks.push_back(Brick(91, 9, 1, 1, false));
    map.bricks.push_back(Brick(92, 9, 1, 1, false));
    map.bricks.push_back(Brick(93, 9, 1, 1, false));

    map.bricks.push_back(Brick(94, 5, 1, 1, false));

    map.bricks.push_back(Brick(100, 5, 1, 1, false));
    map.bricks.push_back(Brick(101, 5, 1, 1, false));

    map.bricks.push_back(Brick(118, 5, 1, 1, false));

    map.bricks.push_back(Brick(121, 9, 1, 1, false));
    map.bricks.push_back(Brick(122, 9, 1, 1, false));
    map.bricks.push_back(Brick(123, 9, 1, 1, false));

    map.bricks.push_back(Brick(128, 9, 1, 1, false));

    map.bricks.push_back(Brick(129, 5, 1, 1, false));
    map.bricks.push_back(Brick(130, 5, 1, 1, false));

    map.bricks.push_back(Brick(131, 9, 1, 1, false));

    map.bricks.push_back(Brick(168, 5, 1, 1, false));
    map.bricks.push_back(Brick(169, 5, 1, 1, false));

    map.bricks.push_back(Brick(171, 5, 1, 1, false));

    map.winblock.SetBBX(198, 2, 1, 10);

    // teleport
    map.teleports.clear();
    // A->B
    map.teleports.push_back(Teleport(57, 6, 2, 1, 0, 50, -4, 48, -15, 16, 15));
    // Testing teleports: start point to A 
    // map.teleports.push_back(Teleport(6, 2, 2, 1, 0, 50, -4, 48, -15, 16, 15));
    // B->A
    map.teleports.push_back(Teleport(59, -13, 2, 1, 0, 164, 4, 160, 0, 16, 15));
    // underground
    map.blocks.push_back(SMBbase(48, -15, 1, 13, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(48, -15, 16, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(61, -13, 5, 2, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(63, -15, 2, 15, bbxr, SMBbase::objectId::BLOCK));
    map.blocks.push_back(SMBbase(52, -13, 7, 3, bbxr, SMBbase::objectId::BLOCK));
    // underground coins
    map.coins.push_back(Coin(52.2, -8, 1, 1));
    map.coins.push_back(Coin(53.3, -8, 1, 1));
    map.coins.push_back(Coin(54.4, -8, 1, 1));
    map.coins.push_back(Coin(55.5, -8, 1, 1));
    map.coins.push_back(Coin(56.6, -8, 1, 1));
    map.coins.push_back(Coin(57.7, -8, 1, 1));

    map.coins.push_back(Coin(53.3, -6, 1, 1));
    map.coins.push_back(Coin(54.4, -6, 1, 1));
    map.coins.push_back(Coin(55.5, -6, 1, 1));
    map.coins.push_back(Coin(56.6, -6, 1, 1));

    InitTexture();
}
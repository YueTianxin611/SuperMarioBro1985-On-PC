#include "teleport.hpp"

Teleport::Teleport(float x, float y, float width, float height, int status,
                   float destx, float desty,
                   float viewPortX, float viewPortY,
                   float viewPortWidth, float viewPortHeight) : SMBbase(x, y, width, height, 0.1, -1)
{
    SetStatus(status);
    SetDest(destx, desty);
    SetDestViewPort(viewPortX, viewPortY, viewPortWidth, viewPortHeight);
}

void Teleport::SetDest(float x, float y)
{
    this->destx = x;
    this->desty = y;
}

void Teleport::SetStatus(int s)
{
    this->status = s;
}

void Teleport::SetDestViewPort(float x, float y, float width, float height)
{
    this->destViewPortX = x;
    this->destViewPortY = y;
    this->destViewPortWidth = width;
    this->destViewPortHeight = height;
}

void Teleport::Transport(Mario &mario)
{
    if (status == Teleport::teleportStatus::ACTIVATE)
    {
        mario.x = destx;
        mario.y = desty;
    }
}
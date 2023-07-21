#ifndef TELEPORT_IS_INCLUDED
#define TELEPORT_IS_INCLUDED

#include "base.hpp"
#include "mario.hpp"

class Teleport : public SMBbase
{
public:
    enum teleportStatus
    {
        ACTIVATE,
        DEACTIVATE,
    };

    int status = Teleport::teleportStatus::DEACTIVATE;
    float destx = 0, desty = 0;
    float destViewPortX = 0, destViewPortY = 0;
    float destViewPortWidth = 0, destViewPortHeight = 0;

    Teleport(float x, float y, float width, float height, int status,
             float destx, float desty,
             float viewPortX, float viewPortY,
             float viewPortWidth, float viewPortHeight);
    void SetDest(float x, float y);
    void SetStatus(int s);
    void SetDestViewPort(float x, float y, float width, float height);
    void Transport(Mario &mario);
};

#endif
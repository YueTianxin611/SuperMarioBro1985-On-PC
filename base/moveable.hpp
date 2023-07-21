#ifndef MOVEABLE_IS_INCLUDED
#define MOVEABLE_IS_INCLUDED

#include "multiStatus.hpp"
class Moveable : public MultiStatus
{
public:
    float vx = 0, vy = 0;
    Moveable();
    Moveable(float x, float y, float width, float height, float bbxRatio, int myId, float vx, float vy);
    virtual void Init() override;
    void SetV(float vx, float vy);
    void SetVX(float vx);
    void SetVY(float vy);
    virtual void MoveByTime(double timeDiff);
};
#endif
#ifndef MULTISTATUS_IS_INCLUDED
#define MULTISTATUS_IS_INCLUDED

#include "base.hpp"

class MultiStatus : public SMBbase
{
public:
    double timeSinceLastStatusChange = 0;

    MultiStatus();
    MultiStatus(float x, float y, float width, float height, float bbxRatio, int myId);
    virtual void Init() override;
    void ClearTimer();
    void AddToTimer(double timeDiff);
};

#endif
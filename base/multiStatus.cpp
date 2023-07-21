#include "multiStatus.hpp"

MultiStatus::MultiStatus()
{
    MultiStatus::Init();
}

MultiStatus::MultiStatus(float x, float y, float width, float height, float bbxRatio, int myId) : SMBbase(x, y, width, height, bbxRatio, myId)
{
    ClearTimer();
}

void MultiStatus::Init()
{
    SMBbase::Init();
    ClearTimer();
}

void MultiStatus::ClearTimer()
{
    timeSinceLastStatusChange = 0;
}

void MultiStatus::AddToTimer(double timeDiff)
{
    timeSinceLastStatusChange += timeDiff;
}
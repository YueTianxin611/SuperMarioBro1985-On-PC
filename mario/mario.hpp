#ifndef MARIO_IS_INCLUDED
#define MARIO_IS_INCLUDED

#include "moveable.hpp"

class Mario : public Moveable
{
public:
    enum marioLocStatus
    {
        ON_GROUND,
        ON_AIR,
    };
    enum marioSizeStatus
    {
        SMALL,
        BIG,
    };
    int currentLocStatus = marioLocStatus::ON_GROUND;
    int currentSizeStatus = marioSizeStatus::SMALL;
    bool currentCanDash = false;
    bool currentVxHasChanged = false;
    bool currentIsRunning = false;
    bool inSizeChange = false;
    double inChangeTime = 0;
    bool isImmortal = false;
    double immortalTime = 0;
    bool onGoomba = false;
    // int lives = 3;
    bool live = true;
    char hitResultAccumulator = 0;
    // m/s
    const float GRAVITY = 30.0;
    const float MAX_WALKING_VX = 5.0;
    const float MAX_DASHING_VX = 8.0;
    const float WALKING_ACC_X = 10.0;
    const float DASHING_ACC_X = 20.0;
    const float JUMP_ACC_Y = 70.0;
    const float NO_INPUT_DEACC_X = 20.0;
    const float MAX_VY = 20.0;
    const float JUMP_TOLERANCE_SEC = 0.3;
    const float EPSILON = 0.01;

    // rendering parameters
    const float RUNNING_ANIMATION_PERIOD = 0.2;
    const float SIZE_CHANGE_PERIOD = 0.8;

    

    Mario();
    Mario(float x, float y, float width, float height, float bbxRatio, float vx, float vy);
    virtual void Init() override;
    void AccRight(double timeDiff);
    void AccLeft(double timeDiff);
    void Jump(double timeDiff);
    void NoXInput(double timeDiff);
    void ApplyGravity(double timeDiff);
    virtual void MoveByTime(double timeDiff) override;
    void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    void CollisionCheckStart();
    void CollisionCheckEnd();
    bool EatMushroom();
    bool EatStar();

    virtual void ApplyRenderStatus() override;
};

#endif
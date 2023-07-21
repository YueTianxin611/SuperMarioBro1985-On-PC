#ifndef BRICK_H_
#define BRICK_H_

#include "moveable.hpp"
#include "mario.hpp"

class Brick : public Moveable
{
public:
    float origin_x_pos;
    float origin_y_pos;
    float max_height;

    bool inair = false;
    bool reachhigh = false;
    bool inmove = false;
    bool destructible = true;
    bool isQuestion = false;
    bool interactive = true; // this is for question block
    // bool stateMutable = true; // true: Mario never collide with this block or collide with special one that can be collided again
    //  false: Mario already collide with this block and is not able to collide again

    enum brickState
    {
        NORMAL = 1,
        DESTROYED = 2,
        WITHQUESTION = 3,
        SOLID = 4
    };

    int brickState = brickState::NORMAL;
    float Y_VELOCITY = 6;
    const float MOVE_UP_DISTANCE = 0.5;

    Brick();
    // Brick(float x, float y, float width, float height, float bbxRatio, float vx, float vy, bool isQ);
    Brick(float x, float y, float width, float height, float vx, float vy, bool isQ);
    Brick(float x, float y, float width, float height, bool isQ);

    void Init() override;
    virtual void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff) override;
    void CollisionUpdateSelf(Mario &other, char collisionResult, double timeDiff);

    void MoveByTime(double timeDiff) override;
    void ApplyRenderStatus() override;

    // helper functions in Brick class
    // void UpdatePos(double timeDiff);
    // void ChangeState(bool largeMario);
    // This method is not mandatory, feel free to delete it.
    void CollisionUpdateMario(Mario &other, char collisionResult, double timeDiff);
};

#endif
#include "base.hpp"

int CollisionResultTest(char collisionResult, bool left, bool right, bool up, bool down)
{
    SMBbase runner;
    if (runner.IsLeftHit(collisionResult) != left)
    {
        printf("IsLeftHit failed\n");
        return 1;
    }
    if (runner.IsRightHit(collisionResult) != right)
    {
        printf("IsRightHit failed\n");
        return 1;
    }
    if (runner.IsDownHit(collisionResult) != down)
    {
        printf("IsDownHit failed\n");
        return 1;
    }
    if (runner.IsUpHit(collisionResult) != up)
    {
        printf("IsUpHit failed\n");
        return 1;
    }
    if (left || right || up || down)
    {
        if (runner.IsNoHit(collisionResult) != false)
        {
            printf("IsNoHit failed\n");
            return 1;
        }
    }
    else
    {
        if (runner.IsNoHit(collisionResult) != true)
        {
            printf("IsNoHit failed\n");
            return 1;
        }
    }
    return 0;
}

int CollisionResultTestInversed(char collisionResult, char supposedResult)
{
    SMBbase runner;
    char inversed = runner.InverseCollision(collisionResult);
    if (inversed != supposedResult)
    {
        printf("CollisionResultTestInversed failed\n");
        return 1;
    }
    return 0;
}

int main()
{
    char collision = 0b0000;
    CollisionResultTest(collision, false, false, false, false);
    collision = 0b0001;
    CollisionResultTest(collision, false, false, false, true);
    collision = 0b0010;
    CollisionResultTest(collision, false, false, true, false);
    collision = 0b0100;
    CollisionResultTest(collision, false, true, false, false);
    collision = 0b1000;
    CollisionResultTest(collision, true, false, false, false);
    collision = 0b1111;
    CollisionResultTest(collision, true, true, true, true);
    collision = 0b1010;
    CollisionResultTest(collision, true, false, true, false);
    collision = 0b0101;
    CollisionResultTest(collision, false, true, false, true);
    collision = 0b1100;
    CollisionResultTest(collision, true, true, false, false);
    collision = 0b0011;
    CollisionResultTest(collision, false, false, true, true);
    collision = 0b1001;
    CollisionResultTest(collision, true, false, false, true);
    collision = 0b0110;
    CollisionResultTest(collision, false, true, true, false);
    collision = 0b1110;
    CollisionResultTest(collision, true, true, true, false);
    collision = 0b1101;
    CollisionResultTest(collision, true, true, false, true);
    collision = 0b1011;
    CollisionResultTest(collision, true, false, true, true);
    collision = 0b0111;
    CollisionResultTest(collision, false, true, true, true);

    CollisionResultTestInversed(0b0000, 0b0000);
    CollisionResultTestInversed(0b0001, 0b0010);
    CollisionResultTestInversed(0b0010, 0b0001);
    CollisionResultTestInversed(0b0100, 0b1000);
    CollisionResultTestInversed(0b1000, 0b0100);

    SMBbase test;
    printf("test id: %d\n", test.myId);
    test.myId = SMBbase::objectId::BLOCK;
    if (test.myId == SMBbase::objectId::BLOCK)
    {
        printf("change success! id: %d\n", test.myId);
    }
    return 0;
}
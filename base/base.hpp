#ifndef BASE_IS_INCLUDED
#define BASE_IS_INCLUDED

#include "renderable.hpp"
class SMBbase
{
    /*
     * This version of collision detection is using the following bounding box:
     *       ----------------
     *     ++                ++
     *     ++                ++
     *     ++                ++
     *     ++                ++
     *     ++                ++
     *       ----------------
     *
     * Where + implyies left and right bounding box
     *       - implies up and down bounding box
     * therefore, it is essentially divide an object into 4 parts
     * up, down, left, right bounding box
     * if up bounding box collides with other object, then it is up hit
     * if down bounding box collides with other object, then it is down hit
     * if left bounding box collides with other object, then it is left hit
     * if right bounding box collides with other object, then it is right hit
     * if up + down + right collides, then it is right hit
     * if up + down + left collides, then it is left hit
     *
     * the bbxRatio is adjusting the thickness of the bounding box
     */
public:
    enum objectId
    {
        UNKNOWN = -1,
        MARIO = 0,
        GOOMBA = 1,
        COIN = 2,
        BLOCK = 3,
        MUSHROOM = 4,
        STAR = 5,
    };
    bool canCollide = true;
    float x = 0, y = 0, width = 0, height = 0;
    float bbxRatio = 0.1;
    Renderable renderer;
    int myId = -1;
    SMBbase();
    SMBbase(float x, float y, float width, float height, float bbxRatio, int myId);
    virtual void Init();
    void SetBBX(float x, float y, float width, float height);
    void SetBBXRatio(float bbxRatio);
    void SetMyId(int id);
    void SetCanCollide(bool canCollide);

    // char has 4 bits:    1    1     1    1
    //                   left right  up   down
    // if no hit: all bits are 0
    char CheckCollision(SMBbase &other);
    char InverseCollision(char collisionResult);
    virtual void CollisionUpdateSelf(SMBbase &other, char collisionResult, double timeDiff);

    /// Render
    virtual void ApplyRenderStatus();

    bool IsNoHit(char collisionResult);
    bool IsLeftHit(char collisionResult);
    bool IsRightHit(char collisionResult);
    bool IsUpHit(char collisionResult);
    bool IsDownHit(char collisionResult);

    bool operator==(const SMBbase &c);

private:
    bool bbxCollisionCheck(float x1, float y1, float width1, float height1,
                           float x2, float y2, float width2, float height2);
};

#endif
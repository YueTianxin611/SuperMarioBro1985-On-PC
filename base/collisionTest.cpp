#include "base.hpp"
#include <stdio.h>

int main()
{
    // AABB coordinates for object 1
    SMBbase base1;
    base1.x = 0.0f;
    base1.y = 0.0f;
    base1.width = 10.0f;
    base1.height = 10.0f;

    // AABB coordinates for object 2
    SMBbase base2;
    base2.x = 10.0f;
    base2.y = 0.0f;
    base2.width = 6.0f;
    base2.height = 6.0f;

    char result = base1.CheckCollision(base2);
    if (base1.IsRightHit(result))
    {
        printf("right hit\n");
    }
    if (base1.IsLeftHit(result))
    {
        printf("left hit\n");
        return 1;
    }
    if (base1.IsUpHit(result))
    {
        printf("up hit\n");
        return 1;
    }
    if (base1.IsDownHit(result))
    {
        printf("down hit\n");
        return 1;
    }

    return 0;
}
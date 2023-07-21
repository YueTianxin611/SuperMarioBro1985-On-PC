#include "textureData.hpp"
#include "renderable.hpp"
#include "textureRegister.h"
#include <fssimplewindow.h>

int TestTextureCoord()
{
    TextureCoord coord(0.1, 0.2, 0.3, 0.4);
    if (coord.TLX() != 0.1)
    {
        printf("TLX failed\n");
        return 1;
    }
    if (coord.TLY() != 0.2)
    {
        printf("TLY failed\n");
        return 1;
    }
    if (coord.TRX() != 0.3)
    {
        printf("TRX failed\n");
        return 1;
    }
    if (coord.TRY() != 0.2)
    {
        printf("TRY failed\n");
        return 1;
    }
    if (coord.BLX() != 0.1)
    {
        printf("BLX failed\n");
        return 1;
    }
    if (coord.BLY() != 0.4)
    {
        printf("BLY failed\n");
        return 1;
    }
    if (coord.BRX() != 0.3)
    {
        printf("BRX failed\n");
        return 1;
    }
    if (coord.BRY() != 0.4)
    {
        printf("BRY failed\n");
        return 1;
    }

    coord.SetCoordByMinMax(0.5, 0.6, 0.7, 0.8);
    if (coord.TLX() != 0.5)
    {
        printf("TLX failed\n");
        return 1;
    }
    if (coord.TLY() != 0.6)
    {
        printf("TLY failed\n");
        return 1;
    }
    if (coord.TRX() != 0.7)
    {
        printf("TRX failed\n");
        return 1;
    }
    if (coord.TRY() != 0.6)
    {
        printf("TRY failed\n");
        return 1;
    }
    if (coord.BLX() != 0.5)
    {
        printf("BLX failed\n");
        return 1;
    }
    if (coord.BLY() != 0.8)
    {
        printf("BLY failed\n");
        return 1;
    }
    if (coord.BRX() != 0.7)
    {
        printf("BRX failed\n");
        return 1;
    }
    if (coord.BRY() != 0.8)
    {
        printf("BRY failed\n");
        return 1;
    }
    return 0;
}

int TestRenderable()
{
    Renderable render;
    render.AddRenderState(0, TextureCoord(0.1, 0.2, 0.3, 0.4));
    render.AddRenderState(1, TextureCoord(0.5, 0.6, 0.7, 0.8));
    render.SetRenderState(0);
    if (render.GetRenderState() != 0)
    {
        printf("GetRenderState failed\n");
        return 1;
    }
    render.SetRenderState(1);
    if (render.GetRenderState() != 1)
    {
        printf("GetRenderState failed\n");
        return 1;
    }
    render.SetRenderTextureId(2);
    if (render.GetRenderTextureId() != 2)
    {
        printf("GetRenderTextureId failed\n");
        return 1;
    }
    render.SetRenderColor(0.1, 0.2, 0.3, 0.4);
    std::vector<float> color = render.GetRenderColor();
    if (color[0] != 0.1 || color[1] != 0.2 || color[2] != 0.3 || color[3] != 0.4)
    {
        printf("GetRenderColor failed\n");
        return 1;
    }
    render.SetRenderVisible(false);
    if (render.GetRenderVisible() != false)
    {
        printf("GetRenderVisible failed\n");
        return 1;
    }
    render.SetRenderVisible(true);
    if (render.GetRenderVisible() != true)
    {
        printf("GetRenderVisible failed\n");
        return 1;
    }
    return 0;
}

int TestTextureData()
{
    TextureData textures;
    textures.resize(2);
    int res = textures.decoders[0].Decode("/Users/gx/repo/24783_cpp/ArcadeAvenger/assets/world1-1.png");
    if (YSERR == res)
    {
        printf("======\ndecode map failed\n======\n");
    }
    else
    {
        printf("======\ndecode map success\n======\n");
    }

    res = textures.decoders[1].Decode("/Users/gx/repo/24783_cpp/ArcadeAvenger/assets/tileset.png");
    if (YSERR == res)
    {
        printf("======\ndecode tileset failed\n======\n");
    }
    else
    {
        printf("======\ndecode tileset success\n======\n");
    }
    return 0;
}

int main()
{
    TestTextureCoord();
    TestRenderable();
    TestTextureData();
}
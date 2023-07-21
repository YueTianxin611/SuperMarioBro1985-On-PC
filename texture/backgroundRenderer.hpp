#ifndef BACKGROUNDRENDERER_IS_INCLUDED
#define BACKGROUNDRENDERER_IS_INCLUDED

#include "textureData.hpp"

class BackgroundRenderer
{
public:
    int textureId = 0;
    float xMinProp = 0, yMinProp = 0, xMaxProp = 0, yMaxProp = 0;

    BackgroundRenderer(){};
    void SetTextureId(int id);
    void SetProp(float xmin, float ymin, float xmax, float ymax);
    void Draw(TextureData &td, float screenWidth, float screenHeight);
};

#endif
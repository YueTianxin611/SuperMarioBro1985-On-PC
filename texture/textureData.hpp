#ifndef TEXTUREDATA_IS_INCLUDED
#define TEXTUREDATA_IS_INCLUDED

#include "fssimplewindow.h"
#include "yspng.h"
#include <vector>

class TextureData
{
public:
    std::vector<YsRawPngDecoder> decoders;
    std::vector<GLuint> texIds;
    std::vector<float> rgba;
    int size = 0;

    void resize(int length);
    void setRGBA(float c[]);
};

#endif
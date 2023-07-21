#include "textureData.hpp"

void TextureData::resize(int length)
{
    size = length < 0 ? 0 : length;
    decoders.resize(size);
    texIds.resize(size);
    rgba.resize(4 * size);
}

void TextureData::setRGBA(float c[])
{
    for (int i = 0; i < size * 4; ++i)
    {
        rgba[i] = c[i];
    }
}
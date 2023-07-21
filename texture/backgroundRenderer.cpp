#include "backgroundRenderer.hpp"

void BackgroundRenderer::SetProp(float xmin, float ymin, float xmax, float ymax)
{
    xMinProp = xmin;
    yMinProp = ymin;
    xMaxProp = xmax;
    yMaxProp = ymax;
}

void BackgroundRenderer::SetTextureId(int id)
{
    textureId = id;
}

void BackgroundRenderer::Draw(TextureData &td, float screenWidth, float screenHeight)
{
    glBindTexture(GL_TEXTURE_2D, td.texIds[textureId]);
    glBegin(GL_QUADS);
    glColor4f(1, 1, 1, 1);
    glTexCoord2f(xMinProp, yMinProp);
    glVertex2f(0, 0);
    glTexCoord2f(xMaxProp, yMinProp);
    glVertex2f(screenWidth, 0);
    glTexCoord2f(xMaxProp, yMaxProp);
    glVertex2f(screenWidth, screenHeight);
    glTexCoord2f(xMinProp, yMaxProp);
    glVertex2f(0, screenHeight);
    glEnd();
}
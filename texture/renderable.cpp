#include "renderable.hpp"
#include "fssimplewindow.h"
// =======================================================
// TextureCoord
TextureCoord::TextureCoord(const float data[4])
{
    SetCoordByMinMax(data);
}

TextureCoord::TextureCoord(float xmin, float ymin, float xmax, float ymax)
{
    SetCoordByMinMax(xmin, ymin, xmax, ymax);
}

void TextureCoord::SetCoordByMinMax(float xmin, float ymin, float xmax, float ymax)
{
    xMin = xmin;
    yMin = ymin;
    xMax = xmax;
    yMax = ymax;
}

void TextureCoord::SetCoordByMinMax(const float data[4])
{
    SetCoordByMinMax(data[0], data[1], data[2], data[3]);
}

float TextureCoord::TLX() const
{
    return xMin;
}
float TextureCoord::TLY() const
{
    return yMin;
}
float TextureCoord::TRX() const
{
    return xMax;
}
float TextureCoord::TRY() const
{
    return yMin;
}
float TextureCoord::BLX() const
{
    return xMin;
}
float TextureCoord::BLY() const
{
    return yMax;
}
float TextureCoord::BRX() const
{
    return xMax;
}
float TextureCoord::BRY() const
{
    return yMax;
}

// =======================================================
// Renderable

void Renderable::AddRenderState(int stateId, TextureCoord texCoord)
{
    state2texture[stateId] = texCoord;
}

void Renderable::SetRenderState(int newState)
{
    currState = newState;
}

void Renderable::SetRenderTextureId(int texId)
{
    textureId = texId;
}

void Renderable::SetRenderColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void Renderable::SetRenderVisible(bool isVisible)
{
    this->isVisible = isVisible;
}

void Renderable::SetRenderIsFlip(bool isFlip)
{
    this->isFlip = isFlip;
}

void Renderable::SetRenderIsUpSideDown(bool isUpSideDown)
{
    this->isUpSideDown = isUpSideDown;
}

int Renderable::GetRenderState() const
{
    return currState;
}
int Renderable::GetRenderTextureId() const
{
    return textureId;
}
std::vector<float> Renderable::GetRenderColor() const
{
    return color;
}
bool Renderable::GetRenderVisible() const
{
    return isVisible;
}
void Renderable::Draw(int openglTexId, float xmin, float ymin, float xmax, float ymax)
{
    if (!isVisible)
    {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, openglTexId);
    Draw(xmin, ymin, xmax, ymax);
}
void Renderable::Draw(TextureData &td, float xmin, float ymin, float xmax, float ymax)
{
    if (!isVisible)
    {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, td.texIds[textureId]);
    Draw(xmin, ymin, xmax, ymax);
}
void Renderable::Draw(float xmin, float ymin, float xmax, float ymax)
{
    TextureCoord &tc = state2texture[currState];
    glBegin(GL_QUADS);
    glColor4f(color[0], color[1], color[2], color[3]);
    if (isFlip && !isUpSideDown)
    {
        // top left
        glTexCoord2f(tc.TRX(), tc.TRY()); // texture top right
        glVertex2f(xmin, ymin);
        // top right
        glTexCoord2f(tc.TLX(), tc.TLY()); // texture top left
        glVertex2f(xmax, ymin);
        // bottom right
        glTexCoord2f(tc.BLX(), tc.BLY()); // texture bottom left
        glVertex2f(xmax, ymax);
        // bottom left
        glTexCoord2f(tc.BRX(), tc.BRY()); // texture bottom right
        glVertex2f(xmin, ymax);
    }
    else if (!isFlip && !isUpSideDown)
    {
        glTexCoord2f(tc.TLX(), tc.TLY()); // top left
        glVertex2f(xmin, ymin);

        glTexCoord2f(tc.TRX(), tc.TRY()); // top right
        glVertex2f(xmax, ymin);

        glTexCoord2f(tc.BRX(), tc.BRY()); // bottom right
        glVertex2f(xmax, ymax);

        glTexCoord2f(tc.BLX(), tc.BLY()); // bottom left
        glVertex2f(xmin, ymax);
    }
    else if (isFlip && isUpSideDown)
    {
        glTexCoord2f(tc.BRX(), tc.BRY()); // texture bottom right
        glVertex2f(xmin, ymin);

        glTexCoord2f(tc.BLX(), tc.BLY()); // texture bottom left
        glVertex2f(xmax, ymin);

        glTexCoord2f(tc.TLX(), tc.TLY()); // texture top left
        glVertex2f(xmax, ymax);

        glTexCoord2f(tc.TRX(), tc.TRY()); // texture top right
        glVertex2f(xmin, ymax);
    }
    else
    {
        glTexCoord2f(tc.BLX(), tc.BLY()); // texture bottom left
        glVertex2f(xmin, ymin);

        glTexCoord2f(tc.BRX(), tc.BRY()); // texture bottom right
        glVertex2f(xmax, ymin);

        glTexCoord2f(tc.TRX(), tc.TRY()); // texture top right
        glVertex2f(xmax, ymax);

        glTexCoord2f(tc.TLX(), tc.TLY()); // texture top left
        glVertex2f(xmin, ymax);
    }

    glEnd();
}

void Renderable::DrawSimple(float xmin, float ymin, float xmax, float ymax)
{
    if (!isVisible)
    {
        return;
    }
    glBegin(GL_QUADS);
    glColor4f(color[0], color[1], color[2], color[3]);
    // top left
    glVertex2f(xmin, ymin);
    // top right
    glVertex2f(xmax, ymin);
    // bottom right
    glVertex2f(xmax, ymax);
    // bottom left
    glVertex2f(xmin, ymax);
    glEnd();
}
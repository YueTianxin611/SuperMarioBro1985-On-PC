#ifndef RENDERABLE_IS_INCLUDED
#define RENDERABLE_IS_INCLUDED

#include <vector>
#include <map>
#include "textureData.hpp"

class TextureCoord
{
public:
    float xMin = 0.;
    float yMin = 0.;
    float xMax = 0.;
    float yMax = 0.;

    TextureCoord(){};
    TextureCoord(float xmin, float ymin, float xmax, float ymax);
    TextureCoord(const float data[4]);
    void SetCoordByMinMax(float xmin, float ymin, float xmax, float ymax);
    void SetCoordByMinMax(const float data[4]);
    float TLX() const;
    float TLY() const;
    float TRX() const;
    float TRY() const;
    float BLX() const;
    float BLY() const;
    float BRX() const;
    float BRY() const;
};

class Renderable
{
public:
    int textureId = 1; // the texture id it needs to bind (related to textureData class)
    int currState = 0;
    bool isVisible = true;
    bool isFlip = false;
    bool isUpSideDown = false;
    std::map<int, TextureCoord> state2texture;
    std::vector<float> color;

    Renderable()
    {
        color.push_back(1.);
        color.push_back(1.);
        color.push_back(1.);
        color.push_back(1.);
    };
    void AddRenderState(int stateId, TextureCoord texCoord);
    void SetRenderState(int newState);
    void SetRenderTextureId(int texId);
    void SetRenderColor(float r, float g, float b, float a);
    void SetRenderVisible(bool isVisible);
    void SetRenderIsFlip(bool isFlip);
    void SetRenderIsUpSideDown(bool isUpSideDown);
    int GetRenderState() const;
    int GetRenderTextureId() const;
    std::vector<float> GetRenderColor() const;
    bool GetRenderVisible() const;
    void Draw(int openglTexId, float xmin, float ymin, float xmax, float ymax);
    void Draw(TextureData &td, float xmin, float ymin, float xmax, float ymax);
    void DrawSimple(float xmin, float ymin, float xmax, float ymax);

private:
    void Draw(float xmin, float ymin, float xmax, float ymax);
};

#endif
#include "textureData.hpp"
#include "renderable.hpp"
#include "textureRegister.h"
#include <fssimplewindow.h>
#include <algorithm>

class ApplicationMain
{
public:
    bool term = false;
    TextureData textures;
    // start percentage
    double x_percent = 0;
    // constants:
    // percentage related to world1-1png's size
    // on Y axis, the world is 240 pixels, 4 times is 960
    const int window_x_len = 960;
    const int window_y_len = 960;
    const double max_x_percent = (3376. - 240.) / 3376.;
    const double x_percent_len = 240. / 3376.;
    Renderable marioRender;

    ApplicationMain();
    ~ApplicationMain();
    void InitTexture();
    bool MustTerminate(void);
    void RunOneStep(void);
    void Draw(void);
};

ApplicationMain::ApplicationMain()
{
    InitTexture();
}

ApplicationMain::~ApplicationMain()
{
}

void ApplicationMain::InitTexture()
{
    // 1 means 1 texture file
    textures.resize(2);
    // must use absolute path and I don't know why
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
    // color means the background color. using white here
    float color[] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    textures.setRGBA(color);

    // register texture to opengl.
    // using for loop since might have multiple textures.
    int rgba_idx = 0;
    glEnable(GL_TEXTURE_2D);
    for (int i = 0; i < textures.size; ++i)
    {
        rgba_idx = i * 4;
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor4d(textures.rgba[rgba_idx],
                  textures.rgba[rgba_idx + 1],
                  textures.rgba[rgba_idx + 2],
                  textures.rgba[rgba_idx + 3]);
        glGenTextures(1, &textures.texIds[i]);
        glBindTexture(GL_TEXTURE_2D, textures.texIds[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGBA,
                     textures.decoders[i].wid,
                     textures.decoders[i].hei,
                     0,
                     GL_RGBA,
                     GL_UNSIGNED_BYTE,
                     textures.decoders[i].rgba);
    }
    TextureRegister tr;

    marioRender.AddRenderState(0, TextureCoord(tr.SMALL_MARIO_STAND));
    marioRender.AddRenderState(1, TextureCoord(tr.SMALL_MARIO_WALK_0));
    marioRender.AddRenderState(2, TextureCoord(tr.SMALL_MARIO_WALK_1));
    marioRender.AddRenderState(3, TextureCoord(tr.SMALL_MARIO_WALK_2));
    marioRender.AddRenderState(4, TextureCoord(tr.SMALL_MARIO_JUMP));
    marioRender.AddRenderState(5, TextureCoord(tr.SMALL_MARIO_GG));
    marioRender.SetRenderState(0);
    marioRender.SetRenderTextureId(1); // second texture
}

bool ApplicationMain::MustTerminate()
{
    return term;
}

void ApplicationMain::RunOneStep()
{
    FsPollDevice();
    int key = FsInkey();
    double move_step = 0.01;
    switch (key)
    {
    case FSKEY_ESC:
        term = true;
        break;
    case FSKEY_LEFT:
        x_percent = std::max(x_percent - move_step, 0.);
        break;
    case FSKEY_RIGHT:
        x_percent = std::min(x_percent + move_step, max_x_percent);
        break;
    case FSKEY_0:
        marioRender.SetRenderState(0);
        break;
    case FSKEY_1:
        marioRender.SetRenderState(1);
        break;
    case FSKEY_2:
        marioRender.SetRenderState(2);
        break;
    case FSKEY_3:
        marioRender.SetRenderState(3);
        break;
    case FSKEY_4:
        marioRender.SetRenderState(4);
        break;
    case FSKEY_5:
        marioRender.SetRenderState(5);
        break;
    }
}

void ApplicationMain::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // bind the first texture
    glBindTexture(GL_TEXTURE_2D, textures.texIds[0]);
    glBegin(GL_QUADS);
    glColor4d(1.0, 1.0, 1.0, 1.0);
    glTexCoord2d(x_percent, 0.0); // top left
    glVertex2d(0, 0);
    glTexCoord2d(x_percent + x_percent_len, 0.0); // top right
    glVertex2d(window_x_len - 1, 0);
    glTexCoord2d(x_percent + x_percent_len, 0.5); // bottom right
    glVertex2d(window_x_len - 1, window_y_len - 1);
    glTexCoord2d(x_percent, 0.5); // bottom left
    glVertex2d(0, window_y_len - 1);
    glEnd();

    marioRender.Draw(textures, 100, 100, 200, 200);

    glDisable(GL_BLEND);
    FsSwapBuffers();
}

int main()
{
    FsOpenWindow(32, 32, 960, 960, 1);
    ApplicationMain app;
    while (true != app.MustTerminate())
    {
        app.RunOneStep();
        app.Draw();
        FsSleep(10);
    }
    return 0;
}
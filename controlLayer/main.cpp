#include "controller.hpp"
#include <chrono>
#include "fssimplewindow.h"
#include "moveable.hpp"
int main()
{
    FsChangeToProgramDir();
    FsOpenWindow(32, 32, 600, 600, 1);
    Controller c;
    auto now = std::chrono::system_clock::now();
    double time_interval = 0;
    while (true != c.IsTerminated())
    {   
        FsGetWindowSize(c.screenWidth, c.screenHeight);
        auto next_now = std::chrono::system_clock::now();
        time_interval = double(std::chrono::duration_cast<std::chrono::milliseconds>(next_now - now).count()) / 1000.0;
        now = next_now;

        c.RunOneStep(time_interval);
        c.Draw();
        FsSleep(10);
    }
}
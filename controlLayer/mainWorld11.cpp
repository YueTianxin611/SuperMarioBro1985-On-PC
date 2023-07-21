#include "controller.hpp"
#include <chrono>
#include "fssimplewindow.h"

int main()
{
    FsChangeToProgramDir();
    FsOpenWindow(32, 32, 512, 480, 1);
    Controller c;
    c.InitWorld11();
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
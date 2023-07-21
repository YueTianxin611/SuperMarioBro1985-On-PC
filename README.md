# Clone & Build this repository
This repository hosts the software of the attemp to remake Super Mario Bros. This repository supports building on Windows, MacOS, Linux.

## Clone this repository
open a teriminal in the location where you want to clone this repository and run 
`git clone https://ramennoodle.me.cmu.edu/Bonobo.Git.Server/ArcadeAvenger.git`

## Build this repository
Before building, make sure you have CMake installed, and the minimum version should be 3.8.
1. Since we're using a library from captainys, you need to clone it first. In the same location where you clone this repository, run 
```
git clone https://github.com/captainys/public.git
git clone https://github.com/captainys/MMLPlayer.git
```
2. Then create a build direcotry 
`mkdir build && cd build`
3. Now you shoule be under the build directory, run
```
cmake -DCMAKE_BUILD_TYPE=Release ../ArcadeAvenger
cmake --build . --target w11test --config Release
```
4. After successfully building the game, you file structure should look like similar to this
```
/'path-to-file-where-you-cloned'
--/ArcadeAvenger
--/build
--/public
......
```

# Launch the game
To run the game, depends on what plattform you're on. (run under build directory)
## On Windows
`controlLayer/Release/w11test.exe` (might be different)
## On MacOs
`./controlLayer/w11test.app/Contents/MacOS/w11test`
## On Linux
`./controlLayer/w11test`


# Credits
Texture: Xin  
Map: Yanran    
Mario (2 people): Tao & Rong  
Collision: Yihe  
Architecture: Tianxin  

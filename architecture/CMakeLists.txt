add_library(libBlock brick.hpp brick.cpp teleport.hpp teleport.cpp)

target_include_directories(libBlock PUBLIC .)
target_link_libraries(libBlock
    libController
    fssimplewindow
    libTexture
    libBase
    libMario
    libMap
    libNpc)

add_executable(block MACOSX_BUNDLE main.cpp)
target_link_libraries(block
    fssimplewindow
    libTexture
    libBase
    libMario
    libMap
    libController
    libNpc)

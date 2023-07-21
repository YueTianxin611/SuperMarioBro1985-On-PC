add_library(yspng yspng.h yspng.cpp)
target_include_directories(yspng PUBLIC .)

add_library(libTexture
    textureData.hpp
    textureData.cpp
    renderable.hpp
    renderable.cpp
    textureRegister.h
    backgroundRenderer.hpp
    backgroundRenderer.cpp)
target_link_libraries(libTexture fssimplewindow yspng)
target_include_directories(libTexture PUBLIC .)

add_executable(textureDemo MACOSX_BUNDLE texturedemo.cpp)
target_link_libraries(textureDemo libTexture)

add_executable(textureTest MACOSX_BUNDLE textureTest.cpp)
target_link_libraries(textureTest libTexture)

enable_testing()
add_test(NAME textureTest COMMAND textureTest)
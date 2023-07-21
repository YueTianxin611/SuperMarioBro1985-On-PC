add_library(libMap map.hpp map.cpp)
target_link_libraries(libMap libTexture libBase libMario libNpc libBlock)
target_include_directories(libMap PUBLIC .)
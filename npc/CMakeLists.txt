add_library(libNpc
    npc.hpp
    npc.cpp
    coin.hpp
    coin.cpp
    star.hpp
    star.cpp
    mushroom.hpp
    mushroom.cpp
    goomba.hpp
    goomba.cpp
)
target_include_directories(libNpc PUBLIC .)
target_link_libraries(libNpc libBase libTexture libMario)

add_executable(npc MACOSX_BUNDLE main.cpp)
target_link_libraries(npc libNpc)

enable_testing()
add_test(NAME npctest COMMAND npc)
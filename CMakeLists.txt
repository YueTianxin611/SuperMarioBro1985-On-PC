cmake_minimum_required(VERSION 3.8)

project(super_mario_bros)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../public/src ${CMAKE_BINARY_DIR}/public)
add_subdirectory(../MMLPlayer/ym2612 ${CMAKE_BINARY_DIR}/ym2612)
add_subdirectory(../MMLPlayer/mmlplayer ${CMAKE_BINARY_DIR}/mmlplayer)

add_subdirectory(texture)
add_subdirectory(base)
add_subdirectory(mario)
add_subdirectory(map)
add_subdirectory(controlLayer)
add_subdirectory(architecture)
add_subdirectory(npc)
add_subdirectory(ysbitmapfont)

enable_testing()
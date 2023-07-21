add_library(libBase
    base.hpp
    base.cpp
    multiStatus.hpp
    multiStatus.cpp
    moveable.hpp
    moveable.cpp
)
target_link_libraries(libBase libTexture)
target_include_directories(libBase PUBLIC .)

add_executable(baseTest MACOSX_BUNDLE baseTest.cpp)
target_link_libraries(baseTest libBase)

enable_testing()

add_test(NAME baseTest COMMAND basetest)
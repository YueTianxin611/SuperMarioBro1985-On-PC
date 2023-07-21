add_library(ysfont ysglfontdata.h ysglfontdata.c)
target_link_libraries(ysfont fssimplewindow)
target_include_directories(ysfont PUBLIC .)
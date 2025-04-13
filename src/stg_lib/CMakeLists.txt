target_include_directories(
    open_stg_lib PUBLIC include
)
target_sources(
    open_stg_lib PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES modules/sdl2.cppm
)
target_sources(
    open_stg_lib PUBLIC FILE_SET HEADERS TYPE HEADERS FILES include/sdl2.hpp
)
target_sources(
    open_stg_lib PRIVATE Window.cpp Renderer.cpp 
)
target_sources(
    tests PUBLIC test/window_test.cpp
)

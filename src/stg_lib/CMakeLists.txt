target_include_directories(
    open_stg_lib PUBLIC include
)
target_include_directories(
    tests PUBLIC include
)
target_sources(
    open_stg_lib PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES 
    modules/sdl.cppm
)
target_sources(
    open_stg_lib PUBLIC FILE_SET HEADERS TYPE HEADERS FILES 
    include/sdl.hpp
    include/sdl_ttf.hpp
    include/open_game.hpp
)
target_sources(
    open_stg_lib PRIVATE 
    Window.cpp Renderer.cpp Surface.cpp
    Font.cpp Init.cpp
)
target_sources(
    tests PUBLIC test/window_test.cpp test/surface_test.cpp
    test/init_test.cpp
)

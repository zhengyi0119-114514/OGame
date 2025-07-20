target_include_directories(
    open_stg_lib PUBLIC include
)
target_include_directories(
    open_stg_lib PUBLIC modules
)
target_sources(
    open_stg_lib PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    modules/open_stg.cppm
    modules/sdl.cppm
    modules/sdl_ttf.cppm
    modules/og_math.cppm
    modules/opt.cppm
    modules/task.cppm
    modules/error.cppm
)
target_sources(
    open_stg_lib PUBLIC FILE_SET HEADERS TYPE HEADERS FILES
    include/sdl.hpp
    include/sdl_ttf.hpp
    include/og_math_h.hpp
    include/og_task_h.hpp
    include/open_game.hpp
    include/options.hpp
    include/error_h.hpp
    include/templates_h.hpp
)
target_sources(
    open_stg_lib PRIVATE
    Font.cpp
    Init.cpp
    Window.cpp
    Renderer.cpp
    Surface.cpp
    point.cpp
    task.cpp
    pthread.cpp
    func.cpp
    math.cpp
    image_resource_pool.cpp
    "name_exist_error.cpp"
    ./PtrTexture.cpp
    ./src-view/image.cpp
    ./static_wallpeaper.cpp
)
target_sources(unit_test 
    PRIVATE 
    tests/TestSurfacePool.cpp 
    tests/TestViewObjectPool.cpp
)
if(WIN32)
    target_link_libraries(open_stg_lib PRIVATE ws2_32)
    target_sources(
        open_stg_lib PRIVATE getPOP_Win32.cpp
    )
elseif(UNIX)
    target_sources(
        open_stg_lib PRIVATE getPOP_POSIX.cpp
    )
endif()
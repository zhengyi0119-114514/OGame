target_include_directories(
    open_stg_lib PUBLIC include
)
target_include_directories(
    open_stg_lib PUBLIC modules
)
target_sources(
    open_stg_lib PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
    modules/open_stg.cppm
    modules/math.cppm
    modules/opt.cppm
    modules/task.cppm
    modules/error.cppm

)
target_sources(
    open_stg_lib PUBLIC FILE_SET HEADERS TYPE HEADERS FILES
    include/og.hpp
    include/og_math_h.hpp
    include/og_task_h.hpp
    include/og_module.hpp
    include/og_view.hpp
    include/og_opt_h.hpp
    include/og_error_h.hpp
    include/og_templates_h.hpp
    include/og_sdl3_h.hpp
    include/og_interface.hpp
    include/og_stg_h.hpp
    include/og_module_view_h.hpp
)

target_sources(
    open_stg_lib PRIVATE
    ./InitAndQuit.cpp
    ./pthread.cpp
    ./StgScene.cpp
    ./math.cpp
    ./runAsRootError.cpp
    ./InitException.cpp
    ./Quit.cpp
    ./Program.cpp
    ./src-view/image.cpp
    ./src-view/WindowScreen.cpp
    ./src-view/RotatableImages.cpp
    ./src-view/KeyboardInput.cpp
    ./src-stg/BarrageTrajectory.cpp
    ./src-stg/StgScreen.cpp
)

target_sources(unit_test 
    PRIVATE 
    tests/TestSurfacePool.cpp 
    tests/TestViewObjectPool.cpp
    tests/TestMath.cpp
    tests/StaticAsserts.cpp
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
if(SDL3_FOUND)
    add_subdirectory(src-sdl3)
endif()
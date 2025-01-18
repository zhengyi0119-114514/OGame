target_sources(
    main
    PRIVATE
    Main/Main.cpp
    Views/sdlWindow.cpp
    Views/renderer.cpp
    Views/sdlSurface.cpp
)
target_sources(ogame_modules PRIVATE
    Modules/Math/Point.cpp
    Modules/Math/Circle.cpp
    Modules/Math/Rectangle.cpp
    Modules/Math/Line.cpp
    Modules/Math/Collide.cpp

)


# https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html
if(WIN32)
    add_subdirectory(Platform/Win32)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_subdirectory(Platform/Linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Android")
    add_subdirectory(Platform/Android)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_subdirectory(Platform/Mac)
endif()

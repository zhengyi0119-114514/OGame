target_sources(ogame_c PRIVATE Modules/init.cpp)
target_sources(main PRIVATE Main/main.cpp)


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
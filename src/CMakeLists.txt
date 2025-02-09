target_sources(ogame_modules PRIVATE 
    Modules/Config.cc 
    Modules/GetWindowConfig.cc
    Modules/GetText.cpp
    Views/LoadingPage.cpp
    Views/BasicPage.cxx
    Views/Page.cc
    views/Controls/Text.cpp
    Views/Controls/Button.cpp
    Views/Controls/FormatText.cc
    Resource.cc
)
target_sources(main PRIVATE Main/Main.cc)

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

target_include_directories(open_stg_launcher_lib
    PUBLIC
    include
)

if(ftxui_FOUND)
    target_sources(open_stg_launcher
        PRIVATE
        ftxui/main.cpp
        ftxui/tabs.cpp
    )
endif()
if(WIN32)
    target_include_directories(open_stg_launcher_win32 PRIVATE win32/include)
    target_sources(open_stg_launcher_win32 PRIVATE
        win32/WinMain.cpp
        win32/app.manifest
    )
    target_sources(open_stg_launcher_win32 PRIVATE FILE_SET HEADERS TYPE HEADERS FILES
        win32/include/launcher.hpp
    )
endif()
if(GTK3_FOUND)
    target_sources(open_stg_launcher_gtk3 PRIVATE
        gtk3ver/main.cpp
    )
endif()

add_subdirectory(qt6-ver)
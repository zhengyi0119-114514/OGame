if(Qt6_FOUND)
    qt_standard_project_setup()
    qt_policy(
        SET QTP0001 NEW
    )
    qt_add_executable(open_stg_launcher_qt6)
    set_target_properties(
        open_stg_launcher_qt6 PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )
    target_sources(open_stg_launcher_qt6 PRIVATE
        qt.cpp
    )
endif()
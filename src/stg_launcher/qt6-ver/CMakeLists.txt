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
    target_link_libraries(open_stg_launcher_qt6
        PUBLIC
        open_stg_launcher_lib Qt6::Quick
    )
    target_sources(open_stg_launcher_qt6 PRIVATE
        qt.cpp
    )
    qt_add_qml_module(open_stg_launcher_qt6 
        URI main
        VERSION 1.0
        QML_FILES 
            qmlLauncher.qml
    )
endif()
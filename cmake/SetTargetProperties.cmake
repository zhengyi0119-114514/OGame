set_target_properties(open_stg_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
    WINDOWS_EXPORT_ALL_SYMBOLS TRUE
)
target_compile_features(
    open_stg_lib PUBLIC
    cxx_std_20
    cxx_constexpr
    cxx_nullptr
    c_std_17
)
set_target_properties(
    open_stg_launcher PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)

if(WIN32)
    set_target_properties(open_stg_launcher_win32
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE)

    target_compile_definitions(
        open_stg_launcher_win32 PRIVATE
        UNICODE
        _UNICODE
        _CRT_SECURE_NO_WARNINGS
        __STDC_WANT_LIB_EXT1__=1
        WINDOWS32
    )

    if(NOT MSVC)
        target_compile_definitions(
            open_stg_launcher_win32 PRIVATE
            NOT_MSVC
        )
    endif()

    if(MSVC)
        target_compile_options(open_stg_launcher_win32
            PRIVATE /utf-8
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(open_stg_launcher_win32 PRIVATE
            -finput-charset=UTF-8
            -fexec-charset=UTF-8
        )
    endif()
endif()

if(GTK3_FOUND)
    if(WIN32)
        target_compile_definitions(open_stg_launcher_win32 PRIVATE
            UNICODE
            _UNICODE
            _CRT_SECURE_NO_WARNINGS
            __STDC_WANT_LIB_EXT1__=1
            WINDOWS32
        )
    endif()

    set_target_properties(open_stg_launcher_gtk3
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE)

    if(MSVC)
        target_compile_options(open_stg_launcher_gtk3
            PRIVATE /utf-8
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(open_stg_launcher_gtk3 PRIVATE
            -finput-charset=UTF-8
            -fexec-charset=UTF-8
        )
    endif()
endif()

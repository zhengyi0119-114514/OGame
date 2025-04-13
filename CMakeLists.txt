cmake_minimum_required(VERSION 3.28)
project(open_stg)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(FindPackage)
include(GNUInstallDirs)

add_library(open_stg_lib SHARED)
target_sources(open_stg_lib PRIVATE src/empty.c)

add_executable(abs_game)
target_sources(abs_game PRIVATE src/empty.c)
target_link_libraries(abs_game PRIVATE open_stg_lib)
add_executable(tests)
target_sources(tests PRIVATE src/empty.c)
target_link_libraries(tests PRIVATE open_stg_lib)

target_compile_definitions(
    open_stg_lib PRIVATE UNICODE _UNICODE
)
if(WIN32)
    set_target_properties(open_stg_lib
        PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS TRUE
    )

    if(MSVC)
        # - Fixes msvc toolchain issue
        # cmake dosen't set `CMAKE_HOST_SYSTEM_PROCESSOR` before `project(...)`, which led to the failure of msvc configuration
        if(DEFINED ENV{PROCESSOR_ARCHITEW6432})
            set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITEW6432}")
        elseif(DEFINED ENV{PROCESSOR_ARCHITECTURE})
            set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITECTURE}")
        endif()

        target_compile_options(
            open_stg_lib
            PUBLIC
            /utf-8
        )
        target_compile_definitions(
            open_stg_lib
            PUBLIC
            _CRT_SECURE_NO_WARNINGS
        )
    endif()
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(
        open_stg_lib 
        PUBLIC 
        LINUX=true
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(NOTICE "Debug")
    target_compile_definitions(
        open_stg_lib
        PRIVATE
        _DEBUG
        DEBUG
    )
endif()

enable_testing()
include(CTest)
include(Catch)
add_subdirectory(src/stg_lib)
add_subdirectory(src/abs_game)
include(LinkLibrary)
include(SetTargetProperties)



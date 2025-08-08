cmake_minimum_required(VERSION 3.28)
project(open_stg VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(FindPackage)
include(GNUInstallDirs)

option(USE_SDL_CLOCK "Use SDL2's clock instead of system clock" FALSE)

add_library(open_stg_launcher_lib SHARED)
target_sources(open_stg_launcher_lib PRIVATE src/empty.c)

add_library(open_stg_lib SHARED)
target_sources(open_stg_lib PRIVATE src/empty.c)

add_executable(abs_game)
target_sources(abs_game PRIVATE src/empty.c)
target_link_libraries(abs_game PRIVATE open_stg_lib)

add_executable(unit_test)
target_sources(unit_test PRIVATE src/empty.c)

target_compile_definitions(
    open_stg_lib PRIVATE UNICODE _UNICODE
)

if(GTK3_FOUND)
    add_executable(open_stg_launcher_gtk3)
    target_sources(open_stg_launcher_gtk3 PRIVATE src/empty.c)
endif()
if(WIN32)
    add_executable(open_stg_launcher_win32 WIN32)
    target_sources(open_stg_launcher_win32 PRIVATE src/empty.c)

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

    target_compile_definitions(
        open_stg_lib
        PUBLIC
        WINDOWS32
    )
elseif(UNIX)
    target_compile_definitions(
        open_stg_lib
        PRIVATE
        POSIX=true
    )
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

add_subdirectory(src/stg_lib)
add_subdirectory(src/abs_game)
add_subdirectory(src/stg_launcher)
add_subdirectory(tests)
include(LinkLibrary)
include(SetTargetProperties)
include(GoogleTest)

gtest_discover_tests(unit_test)

# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# 如果是 Windows/MSVC，使用 copy_directory
add_custom_command(
    TARGET abs_game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RESOURCE_DIR}"
    "$<TARGET_FILE_DIR:abs_game>/resources"
)

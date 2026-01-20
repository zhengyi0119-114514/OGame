cmake_minimum_required(VERSION 3.28)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "请务必别在源代码构建捏，亲。")
endif()

project(open_stg VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(cmake/FindPackage.cmake)
include(cmake/SetGlobalProperties.cmake)
include(GNUInstallDirs)

option(USE_SDL_CLOCK "Use SDL3's clock instead of system clock" FALSE)

add_library(open_stg_lib SHARED src/empty.c)
add_library(open_stg_base_lib SHARED src/empty.c)
add_library(open_stg_sdl_lib SHARED src/empty.c)
add_library(open_stg_net_lib SHARED src/empty.c)
add_library(open_stg_shared INTERFACE)

add_executable(test_game)
target_sources(test_game PRIVATE src/empty.c)

add_executable(unit_test)
target_sources(unit_test PRIVATE src/empty.c)

ADD_CRATE(open_stg_logic_lib
    CRATE_TYPE "SHARED"
    SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS open_stg_base_lib
)

add_subdirectory(src/stg_lib)
add_subdirectory(src/test_game)
include(LinkLibrary)
include(SetTargetProperties)

enable_testing()
include(CTest)
add_subdirectory(tests)

# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# 如果是 Windows/MSVC，使用 copy_directory
add_custom_command(
    TARGET test_game POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory_if_different" "${RESOURCE_DIR}" "$<TARGET_FILE_DIR:test_game>/resources"
)
add_custom_command(
    TARGET test_game PRE_BUILD
    COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props" "${CMAKE_BINARY_DIR}/Directory.Build.props"
)

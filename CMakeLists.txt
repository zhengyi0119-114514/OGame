cmake_minimum_required(VERSION 3.28)
project(open_stg VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(cmake/FindPackage.cmake)
include(GNUInstallDirs)

option(USE_SDL_CLOCK "Use SDL2's clock instead of system clock" FALSE)

add_library(open_stg_lib SHARED src/empty.c)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/include")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")
endif()

configure_file("${CMAKE_SOURCE_DIR}/cmake/ProjectInformation.h.in" "${CMAKE_BINARY_DIR}/include/ProjectImformation.h")
target_include_directories(open_stg_lib PUBLIC "${CMAKE_BINARY_DIR}/include")

add_executable(test_game)
target_sources(test_game PRIVATE src/empty.c)
target_link_libraries(test_game PRIVATE open_stg_lib)

add_executable(unit_test)
target_sources(unit_test PRIVATE src/empty.c)

target_compile_definitions(
    open_stg_lib PRIVATE UNICODE _UNICODE
)

ADD_CRATE(ogame_logic_part
    CRATE_TYPE "SHARED"
    SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

if(
    "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsPhone" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "MSYS" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN"
)
endif()

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
    COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory_if_different"
    "${RESOURCE_DIR}"
    "$<TARGET_FILE_DIR:test_game>/resources"
)
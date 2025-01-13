cmake_minimum_required(VERSION 3.20.1)
project(ogame_c)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(FindPackage)
include(GNUInstallDirs)

add_library(ogame_c SHARED src/empty.c)
target_include_directories(ogame_c PUBLIC includes)
set_target_properties(ogame_c
    PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_link_libraries(ogame_c
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(ogame_c PUBLIC log4cplus::log4cplus)

add_executable(main)
target_link_libraries(main PRIVATE ogame_c)
set_target_properties(
    main
    PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

enable_testing()
add_executable(utests)
target_sources(utests PRIVATE src/empty.c)
target_link_libraries(utests PRIVATE ogame_c)
set_target_properties(
    utests
    PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_link_libraries(utests PRIVATE Catch2::Catch2WithMain)
include(CTest)
include(Catch)
catch_discover_tests(utests)

add_subdirectory(src)
add_subdirectory(unit_test)
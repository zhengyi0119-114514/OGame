cmake_minimum_required(VERSION 3.20.1)
project(ogame_c)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

add_library(ogame_c SHARED src/empty.c)
add_subdirectory(src)

enable_testing()
add_executable(tests)
target_sources(tests PRIVATE src/empty.c)
add_subdirectory(tests)

target_include_directories(ogame_c PUBLIC includes)
set_target_properties(ogame_c
    PROPERTIES 
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
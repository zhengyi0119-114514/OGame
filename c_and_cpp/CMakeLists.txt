cmake_minimum_required(VERSION 3.20.1)
project(ogame_modules)

# - Fixes msvc toolchain issue
# cmake dosen't set `CMAKE_HOST_SYSTEM_PROCESSOR` before `project(...)`, which led to the failure of msvc configuration
if(DEFINED ENV{PROCESSOR_ARCHITEW6432})
  set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITEW6432}")
elseif(DEFINED ENV{PROCESSOR_ARCHITECTURE})
  set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITECTURE}")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")
include(FindPackage)
include(GNUInstallDirs)

add_library(ogame_modules SHARED src/empty.c)
target_include_directories(ogame_modules PUBLIC includes)
set_target_properties(ogame_modules
    PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_link_libraries(ogame_modules PUBLIC log4cplus::log4cplus)

if(WIN32)
    target_compile_definitions(
        ogame_modules PRIVATE UNICODE
    )
endif()

if(MSVC)
    target_compile_options(
        ogame_modules
        PUBLIC
        /utf-8
    )
    target_compile_definitions(
        _CRT_SECURE_NO_WARNINGS
        
    )
endif()

add_executable(main)
target_sources(main PRIVATE src/empty.c)
target_link_libraries(main PRIVATE ogame_modules)
set_target_properties(
    main
    PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
)
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(main
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

enable_testing()
add_executable(utests)
target_sources(utests PRIVATE src/empty.c)
target_link_libraries(utests PRIVATE ogame_modules)
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

install(TARGETS ogame_modules main)
add_subdirectory(src)
add_subdirectory(unit_test)
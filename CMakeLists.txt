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
target_link_libraries(ogame_modules PRIVATE spdlog::spdlog_header_only
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    toml11::toml11
    ${SDL2PP_LIBRARIES}
    )
target_include_directories(ogame_modules PRIVATE ${SDL2PP_INCLUDE_DIRS})
message(NOTICE "SB:${SDL2PP_LIBRARIES}")

if(WIN32)
    target_compile_definitions(
        ogame_modules PRIVATE UNICODE _UNICODE
    )
    set_target_properties(ogame_modules
        PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS
    )
endif()

if(MSVC)
    target_compile_options(
        ogame_modules
        PUBLIC
        /utf-8
    )
    target_compile_definitions(
        ogame_modules
        PUBLIC
        _CRT_SECURE_NO_WARNINGS
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(NOTICE "Debug")
    target_compile_definitions(
        ogame_modules
        PRIVATE
        _DEBUG
        DEBUG
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
target_link_libraries(main
    PUBLIC
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_include_directories(main PRIVATE ${SDL2PP_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${SDL2PP_LIBRARIES})
target_link_libraries(main PRIVATE spdlog::spdlog_header_only)

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
execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory" "${CMAKE_SOURCE_DIR}/data" "${CMAKE_BINARY_DIR}/data")

install(TARGETS ogame_modules main)
add_subdirectory(src)
add_subdirectory(unit_test)
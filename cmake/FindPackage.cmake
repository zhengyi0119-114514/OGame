if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

include(FetchContent)

find_package(Boost REQUIRED CONFIG COMPONENTS
    charconv json filesystem program_options
)
find_package(SDL3 CONFIG REQUIRED) 
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
set(__SDL3_TARGETS SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
find_package(spdlog CONFIG REQUIRED)
find_package(Lua REQUIRED 5)
find_package(PkgConfig QUIET)
find_package(Qt6 QUIET COMPONENTS Core Widgets Gui Quick)
if(MSVC)
    find_package(PThreads4W QUIET CONFIG)
endif()
if(PkgConfig_FOUND)
    if(UNIX)
        pkg_check_modules(LIBSAFEC QUIET REQUIRED IMPORTED_TARGET libsafec)
        message(STATUS "LIBSAFEC_FOUND: ${LIBSAFEC_FOUND}")
    endif()

    if(MSVC)
        # do not thing
    else()
        pkg_check_modules(GTK3 QUIET IMPORTED_TARGET gtk+-3.0)
        if(GTK3_FOUND)
            message(STATUS "GTK3_FOUND: ${GTK3_FOUND}")
        endif()
    endif()
endif()

find_package(GTest QUIET CONFIG)
if(NOT GTest_FOUND)
    FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://ghproxy.net/github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(GTest)
endif()

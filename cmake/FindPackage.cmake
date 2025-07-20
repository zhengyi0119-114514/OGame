if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

include(FetchContent)

find_package(Boost REQUIRED CONFIG COMPONENTS
    charconv json filesystem program_options
)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(Lua REQUIRED)

find_package(PkgConfig QUIET)
find_package(Qt6 COMPONENTS Core Widgets Gui Quick)
if(MSVC)
    find_package(PThreads4W QUIET CONFIG)
endif()
if(PkgConfig_FOUND)
    pkg_check_modules(LIBSAFEC QUIET IMPORTED_TARGET libsafec)

    if(LIBSAFEC_FOUND)
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

# find_package(ftxui CONFIG QUIET)
# if(NOT ftxui_FOUND)
#     FetchContent_Declare(
#         ftxui
#         GIT_REPOSITORY https://ghproxy.net/github.com/ArthurSonzogni/FTXUI
#         GIT_TAG v6.1.9 # Replace with the version you want
#     )

#     FetchContent_MakeAvailable(ftxui)
# endif()

find_package(GTest QUIET CONFIG)
if(NOT GTest_FOUND)
    FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://ghproxy.net/github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(GTest)
endif()

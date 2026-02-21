if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

include(FetchContent)

find_package(Boost REQUIRED CONFIG COMPONENTS
    json program_options
)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Lua REQUIRED 5)
find_package(PkgConfig QUIET)
find_package(fmt REQUIRED CONFIG)
find_package(Rust REQUIRED)
find_package(ICU REQUIRED COMPONENTS i18n data io)
find_package(PThreads4W QUIET CONFIG)

if(PkgConfig_FOUND)
    if(UNIX)
        pkg_check_modules(LIBSAFEC QUIET REQUIRED IMPORTED_TARGET libsafec)
        pkg_check_modules(XDG_DESKTOP_PORTAL QUIET IMPORTED_TARGET xdg-desktop-portal)
        pkg_check_modules(GTK4 QUIET IMPORTED_TARGET gtk4)
        pkg_check_modules(MCFGHREAD QUIET IMPORTED_TARGET mcfgthread)
    endif()
endif()

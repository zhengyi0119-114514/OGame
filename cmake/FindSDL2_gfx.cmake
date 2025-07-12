#[[
FindSDL2_gfx.cmake - Finds SDL2_gfx installation

This module finds the SDL2_gfx library and includes.

Input variables:
  SDL2_gfx_ROOT - Preferred installation prefix
  SDL2_gfx_DIR - Alternative directory to look for

Output variables:
  SDL2_gfx_FOUND - True if the package was found
  SDL2_gfx_INCLUDE_DIRS - Include directories
  SDL2_gfx_LIBRARY - Libraries to link against
]]
# if using vcpkg to install SDL2_gfx
set(SDL2_gfx_FOUND FALSE)
include(FindPackageHandleStandardArgs)

if(WIN32)
    if(DEFINED VCPKG_TARGET_TRIPLET)
        find_package(sdl2-gfx CONFIG QUIET)

        if(sdl2-gfx_FOUND)
            set(SDL2_gfx_FOUND TRUE)
            set(__SDL2_GFX_TARGET SDL2::SDL2_gfx)
        endif()
    endif()
endif()

if(NOT SDL2_gfx_FOUND)
    find_package(PkgConfig QUIET)

    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2GFX QUIET IMPORTED_TARGET SDL2_gfx)

        if(SDL2GFX_FOUND)
            set(SDL2_gfx_FOUND TRUE)
            set(__SDL2_GFX_TARGET PkgConfig::SDL2GFX)
            set(SDL2_gfx_INCLUDE_DIR ${SDL2GFX_INCLUDE_DIR})
            set(SDL2_gfx_LIBRARY ${SDL2GFX_LIBRARIES})
        endif()
    endif()
endif()

if(NOT SDL2_gfx_FOUND)
    if(UNIX)
        find_path(SDL2_gfx_INCLUDE_DIR SDL2_gfxPrimitives.h
            PATHS
            /usr/include
            /usr/local/include
            /opt/local/include
            PATH_SUFFIXES SDL2
        )

        find_library(SDL2_gfx_LIBRARY
            NAMES SDL2_gfx
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
        )
    endif()

    if(DEFINED SDL2_gfx_DIR)
    endif()

    if(SDL2_gfx_INCLUDE_DIR AND SDL2_gfx_LIBRARY)
        set(SDL2_gfx_FOUND TRUE)
    endif()
endif()

if(SDL2_gfx_FOUND)
    add_library(SDL2_gfx::SDL2_gfx UNKNOWN IMPORTED)

    if(DEFINED VCPKG_TARGET_TRIPLET) # vcpkg
        set_property(TARGET SDL2_gfx::SDL2_gfx PROPERTY IMPORTED_LOCATION "${sdl2-gfx_DIR}/../../bin/SDL2_gfx.dll")
    else() #PkgConfig
        set_property(TARGET SDL2_gfx::SDL2_gfx PROPERTY IMPORTED_LOCATION "${SDL2_gfx_LIBRARY}")
    endif()

    if(DEFINED __SDL2_GFX_TARGET)
        target_link_libraries(SDL2_gfx::SDL2_gfx INTERFACE ${__SDL2_GFX_TARGET})

    else()
        target_include_directories(SDL2_gfx::SDL2_gfx INTERFACE ${SDL2_gfx_INCLUDE_DIR})
        target_link_libraries(SDL2_gfx::SDL2_gfx INTERFACE ${SDL2_gfx_LIBRARY})
        set_property(TARGET SDL2_gfx::SDL2_gfx PROPERTY IMPORTED_LOCATION "${SDL2_gfx_LIBRARY}")
    endif()
elseif()
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    FOUND_VAR SDL2_gfx_FOUND
    REQUIRED_VARS
    SDL2_gfx_INCLUDE_DIR
    SDL2_gfx_LIBRARY
)
endif()
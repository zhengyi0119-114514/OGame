if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

include(FetchContent)

find_package(Boost REQUIRED CONFIG COMPONENTS
    json filesystem program_options
)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
set(__SDL3_TARGETS SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
find_package(spdlog CONFIG REQUIRED)
find_package(Lua REQUIRED 5)
find_package(PkgConfig QUIET)
find_package(ICU REQUIRED COMPONENTS "i18n" "data" "io")
set(__ICU_TARGETS "ICU::io")

if(TARGET "ICU::dt")
    list(APPEND __ICU_TARGETS "ICU::dt")
elseif(TARGET "ICU::data")
    list(APPEND __ICU_TARGETS "ICU::data")
endif()

if(TARGET "ICU::in")
    list(APPEND __ICU_TARGETS "ICU::in")
elseif(TARGET "ICU::i18n")
    list(APPEND __ICU_TARGETS "ICU::i18n")
endif()

find_package(Rust REQUIRED)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    find_package(PThreads4W QUIET CONFIG)
endif()

if(PkgConfig_FOUND)
    if(UNIX)
        pkg_check_modules(LIBSAFEC QUIET REQUIRED IMPORTED_TARGET libsafec)
    endif()
endif()

# FetchContent_Declare(
# Corrosion
# GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
# GIT_TAG v0.5.2 # Optionally specify a commit hash, version tag or branch here
# )
# FetchContent_MakeAvailable(Corrosion)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

find_package(asio CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)
find_package(Boost REQUIRED CONFIG COMPONENTS 
    thread program_options charconv 
    json property_tree filesystem asio
)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(Lua REQUIRED)

find_package(PkgConfig QUIET)

if(NOT UNIX)
    find_package(PThreads4W REQUIRED)
    target_link_libraries(main PRIVATE PThreads4W::PThreads4W)
endif()

if(PkgConfig_FOUND)
    pkg_check_modules(LIBSAFEC QUIET IMPORTED_TARGET libsafec)
    message(STATUS "LIBSAFEC_FOUND: ${LIBSAFEC_FOUND}")
endif()

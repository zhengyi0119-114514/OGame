target_link_libraries(
    test_game PUBLIC
    open_stg_lib
    spdlog::spdlog
)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/include")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")
endif()

configure_file("${CMAKE_SOURCE_DIR}/cmake/ProjectInformation.h.in" "${CMAKE_BINARY_DIR}/include/ProjectImformation.h")
target_include_directories(open_stg_shared INTERFACE "${CMAKE_BINARY_DIR}/include")
target_link_libraries(open_stg_shared
    INTERFACE
    fmt::fmt
    ICU::data
    ICU::i18n
    ICU::io
    ${LUA_LIBRARIES}
)
target_link_libraries(open_stg_base_lib
    PUBLIC
    Boost::json
    $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBSAFEC>
    $<TARGET_NAME_IF_EXISTS:PThreads4W::PThreads4W>
    PRIVATE
    open_stg_shared
)
target_include_directories(
    open_stg_shared
    INTERFACE
    ${LUA_INCLUDE_DIR}
)
target_link_libraries(open_stg_sdl_lib
    PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    $<TARGET_NAME_IF_EXISTS:PkgConfig::XDG_DESKTOP_PORTAL>
    open_stg_shared
    PUBLIC
    open_stg_base_lib
)
target_link_libraries(open_stg_net_lib PUBLIC
    open_stg_base_lib
    PRIVATE
    open_stg_shared
)
target_link_libraries(
    open_stg_lib
    PUBLIC
    open_stg_base_lib
    open_stg_sdl_lib
    open_stg_net_lib
    open_stg_logic_lib
)

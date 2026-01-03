target_link_libraries(
    test_game PUBLIC
    open_stg_lib
    spdlog::spdlog
)
TARGET_LINK_SHARED_CRATE(open_stg_lib PUBLIC ogame_logic_part)

target_link_libraries(open_stg_lib PUBLIC
    Boost::json
    ${LUA_LIBRARIES}
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    $<IF:$<TARGET_EXISTS:ICU::dt>,ICU::dt,ICU::data>
    $<IF:$<TARGET_EXISTS:ICU::in>,ICU::in,ICU::i18n>
    ICU::io
    fmt::fmt
    spdlog::spdlog
    $<TARGET_NAME_IF_EXISTS:PkgConfig::XDG_DESKTOP_PORTAL>
    $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBSAFEC>
    $<TARGET_NAME_IF_EXISTS:PThreads4W::PThreads4W>
)
TARGET_LINK_SHARED_CRATE(open_stg_lib PUBLIC ogame_logic_part)

target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)

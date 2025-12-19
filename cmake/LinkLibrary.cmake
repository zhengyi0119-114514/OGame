target_link_libraries(
    test_game PUBLIC
    open_stg_lib
    ogame_logic_part
    spdlog::spdlog

)

target_link_libraries(open_stg_lib PUBLIC
    Boost::json
    ogame_logic_part
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
)

target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)

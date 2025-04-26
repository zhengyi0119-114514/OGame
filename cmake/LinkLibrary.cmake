if(${LIBSAFEC_FOUND})
    target_link_libraries(open_stg_lib PUBLIC PkgConfig::LIBSAFEC)
    target_compile_definitions(open_stg_lib PUBLIC LIBSAFEC)
endif()

target_link_libraries(tests PRIVATE
    Catch2::Catch2WithMain open_stg_lib
)
target_link_libraries(
    abs_game PUBLIC open_stg_lib spdlog::spdlog
)
target_link_libraries(open_stg_lib PUBLIC
    asio::asio
    Boost::property_tree Boost::thread Boost::asio 
    Boost::charconv Boost::json Boost::program_options Boost::filesystem
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    ${LUA_LIBRARIES}
)
target_include_directories(open_stg_lib PRIVATE
    ${LUA_INCLUDE_DIR}
)

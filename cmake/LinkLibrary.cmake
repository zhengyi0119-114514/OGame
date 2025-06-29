if(${LIBSAFEC_FOUND})
    target_link_libraries(open_stg_lib PUBLIC PkgConfig::LIBSAFEC)
    target_compile_definitions(open_stg_lib PUBLIC LIBSAFEC)
endif()

target_link_libraries(
    abs_game PUBLIC open_stg_lib
)
target_link_libraries(
    open_stg_launcher PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    ftxui::screen ftxui::dom ftxui::component
    Boost::json
)
target_link_libraries(open_stg_lib PUBLIC
    Boost::charconv Boost::json Boost::filesystem Boost::program_options
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    SDL::SDL_gfx
    ${LUA_LIBRARIES}
)
target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)
target_link_libraries(
    tests PRIVATE GTest::gtest open_stg_lib
)

if(WIN32)
    if(MSVC)
        target_link_libraries(open_stg_lib PUBLIC
            PThreads4W::PThreads4W)
    else()
        target_link_libraries(open_stg_lib PUBLIC
            pthread)
    endif()
endif()

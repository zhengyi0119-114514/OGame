if(${LIBSAFEC_FOUND})
    target_link_libraries(open_stg_lib PUBLIC PkgConfig::LIBSAFEC)
    target_compile_definitions(open_stg_lib PUBLIC LIBSAFEC)
endif()

target_link_libraries(open_stg_launcher_lib
    PUBLIC $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static> Boost::json
)
target_link_libraries(
    abs_game PUBLIC open_stg_lib
)
target_link_libraries(
    open_stg_launcher PRIVATE
    open_stg_launcher_lib
    ftxui::screen ftxui::dom ftxui::component
    Boost::json
)
target_link_libraries(open_stg_lib PUBLIC
    Boost::charconv Boost::json Boost::filesystem Boost::program_options
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    SDL2_gfx::SDL2_gfx
    ${LUA_LIBRARIES}
)
target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)
target_link_libraries(
    tests PRIVATE GTest::gtest open_stg_lib
)

if(GTK3_FOUND)
    target_link_libraries(open_stg_launcher_gtk3
        PUBLIC
        PkgConfig::GTK3
        open_stg_launcher_lib
    )
endif()

if(WIN32)
    target_link_libraries(open_stg_launcher_win32 PRIVATE
        open_stg_launcher_lib
    )

    if(MSVC)
        target_link_libraries(open_stg_lib PUBLIC
            PThreads4W::PThreads4W)
    else()
        target_link_libraries(open_stg_lib PUBLIC
            pthread)
    endif()
endif()

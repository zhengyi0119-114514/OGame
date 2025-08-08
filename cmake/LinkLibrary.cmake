if(${LIBSAFEC_FOUND})
    target_link_libraries(open_stg_lib PUBLIC PkgConfig::LIBSAFEC)
    target_compile_definitions(open_stg_lib PUBLIC LIBSAFEC)
endif()

target_link_libraries(open_stg_launcher_lib
    PUBLIC ${__SDL3_TARGETS} Boost::json
)
target_link_libraries(
    abs_game PUBLIC open_stg_lib
)

target_link_libraries(open_stg_lib PUBLIC
    Boost::charconv Boost::json 
    Boost::filesystem Boost::program_options
    ${LUA_LIBRARIES}
    ${__SDL3_TARGETS}
    spdlog::spdlog
)
target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)
target_link_libraries(
    unit_test PRIVATE GTest::gtest open_stg_lib
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

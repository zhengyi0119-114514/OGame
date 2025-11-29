if(${LIBSAFEC_FOUND})
    target_link_libraries(open_stg_lib PUBLIC PkgConfig::LIBSAFEC)
    target_compile_definitions(open_stg_lib PUBLIC LIBSAFEC)
endif()

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
    ${__SDL3_TARGETS}
    ${__ICU_TARGETS}
    spdlog::spdlog
)
target_include_directories(open_stg_lib PUBLIC
    ${LUA_INCLUDE_DIR}
)
target_link_libraries(
    unit_test PRIVATE open_stg_lib
)

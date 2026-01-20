set_target_properties(
    test_game
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
)

set_target_properties(open_stg_base_lib
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
    POSITION_INDEPENDENT_CODE TRUE
)
set_target_properties(open_stg_sdl_lib
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
    POSITION_INDEPENDENT_CODE TRUE
)
set_target_properties(open_stg_net_lib
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
    POSITION_INDEPENDENT_CODE TRUE
)
target_compile_features(
    open_stg_base_lib PUBLIC
    cxx_std_20
    cxx_constexpr
    cxx_nullptr
    c_std_17
)

target_compile_options(
    open_stg_base_lib
    PUBLIC
    $<$<C_COMPILER_ID:GNU>:-fexec-charset=UTF-8>
    $<$<C_COMPILER_ID:MSVC>:/utf-8>
    $<$<C_COMPILER_ID:MSVC>:/Zc:__cplusplus>
    $<$<C_COMPILER_ID:MSVC>:/Zc:__STDC__>
)
target_compile_options(
    open_stg_shared
    INTERFACE
    $<$<AND:$<C_COMPILER_ID:GNU,AppleClang,ARMClang,CrayClang,TIClang,IntelLLVM,Clang>,$<CONFIG:Release>>:-Ofast>
    $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/Ox>
)
target_compile_definitions(
    open_stg_base_lib
    PUBLIC
    OPEN_STG_MACRO_HAS_XDG_PORTAL=$<BOOL:${XDG_DESKTOP_PORTAL_FOUND}>
    OPEN_STG_MACRO_IS_LINUX=$<PLATFORM_ID:Linux>
    OPEN_STG_MACRO_IS_BSD=$<PLATFORM_ID:FreeBSD,NetBSD,OpenBSD,MirBSD> # 未测试
    OPEN_STG_MACRO_IS_APPLE=$<BOOL:${APPLE}>
    OPEN_STG_MACRO_IS_WINDOWS=$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>
    OPEN_STG_MACRO_IS_DEBUG=$<CONFIG:Debug>
    OPEN_STG_MACRO_IS_RELEASE=$<CONFIG:Release,RelWithDebInfo,MinSizeRel>
)
target_compile_definitions(
    open_stg_shared
    INTERFACE
    UINCODE
    _UNICODE
    $<$<CXX_COMPILER_ID:MSVC,Clang>:_CRT_SECURE_NO_WARNINGS>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:__STDC_WANT_LIB_EXT1__=1>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:WIN32>
    $<$<BOOL:${UNIX}>:POSIX=1>
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Debug>:DEBUG>
)

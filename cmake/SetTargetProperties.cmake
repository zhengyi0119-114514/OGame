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

set_target_properties(open_stg_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS TRUE
    C_STANDARD 17
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
    POSITION_INDEPENDENT_CODE TRUE
)
target_compile_features(
    open_stg_lib PUBLIC
    cxx_std_20
    cxx_constexpr
    cxx_nullptr
    c_std_17
)

target_compile_options(
    open_stg_lib
    PUBLIC
    $<$<C_COMPILER_ID:GNU>:-fexec-charset=UTF-8>
    $<$<C_COMPILER_ID:MSVC>:/utf-8>
    $<$<C_COMPILER_ID:MSVC>:/Zc:__cplusplus>
    $<$<C_COMPILER_ID:MSVC>:/Zc:__STDC__>
    $<$<AND:$<C_COMPILER_ID:GNU,AppleClang,ARMClang,CrayClang,TIClang,IntelLLVM,Clang>,$<CONFIG:Release>>:-Ofast>
    $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/Ox>
)
target_compile_definitions(
    open_stg_lib
    PUBLIC
    $<$<CXX_COMPILER_ID:MSVC,Clang>:_CRT_SECURE_NO_WARNINGS>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:__STDC_WANT_LIB_EXT1__>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:WIN32>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:OPEN_STG_MACRO_IS_WINDOWS=true>
    $<$<BOOL:${UNIX}>:POSIX=true>
    $<$<BOOL:${XDG_DESKTOP_PORTAL_FOUND}>:OPEN_STG_MACRO_HAS_XDG_PORTAL=true>
    $<$<PLATFORM_ID:Linux>:OPEN_STG_MACRO_IS_LINUX=true>
    $<$<PLATFORM_ID:FreeBSD,NetBSD,OpenBSD,MirBSD>:OPEN_STG_MACRO_IS_BSD=true> #未测试
    $<$<BOOL:${APPLE}>:OPEN_STG_MACRO_IS_APPLE=true>
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Debug>:DEBUG>
    UINCODE
    _UNICODE
)



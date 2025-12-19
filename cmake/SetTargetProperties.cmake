find_program(__LLD_FOUND NAMES "lld")

if(
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "ARMClang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IntelLLVM" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CrayClang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IBMClang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "TIClang"
)
    set(__IS_CLANG TRUE)
else()
    set(__IS_CLANG FALSE)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(__IS_GNU TRUE)
else()
    set(__IS_GNU FALSE)
endif()

if(${__IS_GNU} OR ${__IS_CLANG} AND NOT "${__LLD_FOUND}" STREQUAL "__LLD_FOUND-NOTFOUND")
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.29)
        set(CMAKE_LINKER_TYPE LLD)
    else()
        add_link_options("-fuse-ld=lld")
    endif()
endif()

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
    $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    $<$<C_COMPILER_ID:MSVC>:__STDC_WANT_LIB_EXT1__>
    $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:WIN32>
    $<$<BOOL:${UNIX}>:POSIX=true>
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Debug>:DEBUG>
    $<$<BOOL:${XDG_DESKTOP_PORTAL_FOUND}>:OPEN_STG_HAS_XDG_PORTAL=true>
    $<$<PLATFORM_ID:Linux>:OPEN_STG_IS_LINUX=true>
    $<$<PLATFORM_ID:FreeBSD,NetBSD,OpenBSD,MirBSD>:OPEN_STG_IS_BSD=true> #未测试
    $<$<BOOL:${APPLE}>:OPEN_STG_IS_APPLE=true>
)



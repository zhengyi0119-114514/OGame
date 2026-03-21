cmake_minimum_required(VERSION 3.28)
include(CMakeDependentOption)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "请务必别在源代码构建捏，亲。")
endif()

project(open_stg VERSION 0.1.0)

option(OPEN_STG_OPTION_USE_MCFGTHREAD "Will use mcfgthread instead of pthread。" TRUE)
message(STATUS "OPEN_STG_OPTION_USE_MCFGTHREAD:${OPEN_STG_OPTION_USE_MCFGTHREAD}")
option(OPEN_STG_OPTION_USE_SDL3_CLOCK "Use SDL3's clock instead of system clock." FALSE)
message(STATUS "OPEN_STG_OPTION_USE_SDL3_CLOCK:${OPEN_STG_OPTION_USE_SDL3_CLOCK}")
option(OPEN_STG_OPTION_USE_ZIG "OPEN_STG_OPTION_USE_SDL3_CLOCK:${OPEN_STG_OPTION_USE_SDL3_CLOCK}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_SOURCE_DIR}")

include(cmake/SetGlobalProperties.cmake)
include(cmake/AddTarget.cmake)
include(cmake/FindPackage.cmake)
include(GNUInstallDirs)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/include")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")
endif()
configure_file("${CMAKE_SOURCE_DIR}/cmake/ProjectInformation.h.in" "${CMAKE_BINARY_DIR}/include/OpenStg/ProjectInformation.h")

ADD_TARGET(
    open_stg_shared
    TARGET_TYPE INTERFACE
    LINK_DEPENDS
        INTERFACE
            fmt::fmt
            ICU::data
            ICU::i18n
            ICU::io
            ${LUA_LIBRARIES}
    LINK_OPTIONS
        INTERFACE 
            $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>,$<C_COMPILER_ID:GUN,Clang>,$<LINK_LANGUAGE:C,CXX>>:-rdynamic>
    COMPILE_OPTIONS
        INTERFACE
            $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>,$<COMPILE_LANGUAGE:C,CXX>>:/Ox>
            $<$<COMPILE_LANGUAGE:C,CXX>:$<$<C_COMPILER_ID:MSVC>:/W4>>
            $<$<COMPILE_LANGUAGE:C,CXX>:$<$<AND:$<C_COMPILER_ID:GNU,AppleClang,ARMClang,CrayClang,TIClang,IntelLLVM,Clang>,$<CONFIG:Release>>:-Ofast>>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:GNU,AppleClang,ARMClang,CrayClang,TIClang,IntelLLVM,Clang>>:
                -Wall;
                -Wextra;
                -Wno-sign-compare;
                -Wno-unused-parameter
            >
    COMPILE_DEFINITIONS
        INTERFACE
            $<$<COMPILE_LANGUAGE:C,CXX>:UINCODE>
            $<$<COMPILE_LANGUAGE:C,CXX>:_UINCODE>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CXX_COMPILER_ID:MSVC,Clang>>:_CRT_SECURE_NO_WARNINGS>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>>:__STDC_WANT_LIB_EXT1__=1>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CONFIG:Debug>>:_DEBUG=1>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CONFIG:Debug>>:DEBUG=1>
    INCLUDE_DIRS
        INTERFACE
            ${LUA_INCLUDE_DIR}
)

ADD_TARGET(
    open_stg_base_lib
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PUBLIC
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBSAFEC>
        PRIVATE
            $<$<CONFIG:Debug>:$<TARGET_NAME_IF_EXISTS:libdwarf::dwarf>>
            $<$<CONFIG:Debug>:$<TARGET_NAME_IF_EXISTS:PkgConfig::DWARF>>
            open_stg_shared
            Boost::json
            $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:dbghelp>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::MCFGHREAD>
            $<TARGET_NAME_IF_EXISTS:PThreads4W::PThreads4W>
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
        POSITION_INDEPENDENT_CODE TRUE
    LINK_OPTIONS
    COMPILE_FEATURES
        PUBLIC
            cxx_std_20
            cxx_constexpr
            cxx_nullptr
            c_std_17
    COMPILE_OPTIONS
        PUBLIC
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:GNU>>:-fexec-charset=UTF-8;-finput-charset=UTF-8>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:MSVC>>:/source-charset:utf-8;/execution-charset:utf-8>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:MSVC>>:/Zc:__cplusplus>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:MSVC>>:/Zc:__STDC__>
    COMPILE_DEFINITIONS
        PUBLIC
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_LINUX=$<PLATFORM_ID:Linux>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_BSD=$<PLATFORM_ID:FreeBSD,NetBSD,OpenBSD,MirBSD>> # 未测试
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_APPLE=$<BOOL:${APPLE}>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_WINDOWS=$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_DEBUG=$<CONFIG:Debug>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_IS_RELEASE=$<CONFIG:Release,RelWithDebInfo,MinSizeRel>>
        PRIVATE
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_OPTION_USE_MCFGTHREAD=$<AND:$<BOOL:${OPEN_STG_OPTION_USE_MCFGTHREAD}>,$<BOOL:${MCFGHREAD_FOUND}>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_OPTION_USE_SDL3_CLOCK=$<BOOL:${OPEN_STG_OPTION_USE_SDL3_CLOCK}>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_HAS_XDG_PORTAL=$<BOOL:${XDG_DESKTOP_PORTAL_FOUND}>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_LIBDWARF=$<AND:$<CONFIG:Debug>,$<OR:$<TARGET_EXISTS:libdwarf::dwarf>,$<TARGET_EXISTS:PkgConfig::DWARF>>>>
    INCLUDE_DIRS
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
ADD_CRATE(open_stg_base_lib_wapper
    IMPORTED_TARGET
    CRATE_TYPE "dylib"
    MANIFEST_FILE Cargo.toml
    LINK_LIBRARIES
        PUBLIC_TARGET 
            open_stg_base_lib
)
ADD_TARGET(
    open_stg_graphics_lib
    TARGET_TYPE SHARED
    LINK_DEPENDS 
        PRIVATE
            SDL3::SDL3
            SDL3_ttf::SDL3_ttf
            SDL3_image::SDL3_image
            $<TARGET_NAME_IF_EXISTS:PkgConfig::XDG_DESKTOP_PORTAL>
            open_stg_shared
        PUBLIC
            open_stg_base_lib        
    LINK_OPTIONS
    COMPILE_OPTIONS
    COMPILE_DEFINITIONS
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
        POSITION_INDEPENDENT_CODE TRUE
)
ADD_TARGET(
    open_stg_net_lib
    TARGET_TYPE SHARED
    LINK_DEPENDS 
        PRIVATE
            open_stg_shared
            $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:ws2_32>
        PUBLIC
            open_stg_base_lib
    LINK_OPTIONS
    COMPILE_OPTIONS
    COMPILE_DEFINITIONS
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
        POSITION_INDEPENDENT_CODE TRUE
)

ADD_CRATE(open_stg_logic_lib
    IMPORTED_TARGET
    CRATE_TYPE "cdylib"
    MANIFEST_FILE Cargo.toml
    TARGET_ALIAS_NAME open_stg_logic_lib
    DEPENDS open_stg_base_lib_wapper
)
ADD_TARGET(
    open_stg_lib
    TARGET_TYPE INTERFACE
    LINK_DEPENDS 
        INTERFACE     
            open_stg_base_lib
            open_stg_graphics_lib
            open_stg_net_lib
            open_stg_logic_lib
)
ADD_TARGET(
    test_game
    TARGET_TYPE EXE
    LINK_DEPENDS
        PUBLIC
            open_stg_lib
            spdlog::spdlog
    COMPILE_OPTIONS
    COMPILE_DEFINITIONS
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
)
ADD_TARGET(
    unit_test
    TARGET_TYPE EXECUTABLE
    LINK_DEPENDS
        PUBLIC
        open_stg_lib
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
)

add_subdirectory(src-c_and_cpp/stg_lib)
add_subdirectory(src-c_and_cpp/test_game)

enable_testing()
include(CTest)
add_subdirectory(tests)

# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
# 如果是 Windows/MSVC，使用 copy_directory
# add_custom_command(
#     TARGET test_game POST_BUILD
#     COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory_if_different" "${RESOURCE_DIR}" "$<TARGET_FILE_DIR:test_game>/resources"
# )
# add_custom_command(
#     TARGET test_game PRE_BUILD
#     COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props" "${CMAKE_BINARY_DIR}/Directory.Build.props"
# )

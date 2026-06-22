cmake_minimum_required(VERSION 3.28)
include(CMakeDependentOption)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "请务必别在源代码构建捏，亲。")
endif()

project(open_stg VERSION 0.1.0)

if(NOT DEFINED OPEN_STG_LOADER_MODULE)
    if("${CMAKE_SYSTEM_NAME}" MATCHES [=[^(Windows|WindowsPhone|WindowsStore|MSYS)$]=])
        set(OPEN_STG_LOADER_MODULE "OneProcess")
    elseif("${UNIX}")
        set(OPEN_STG_LOADER_ARCHITECTURE "MicrokernelLikeArchitecture")
    endif()
endif()

if(NOT "${OPEN_STG_LOADER_ARCHITECTURE}" MATCHES [=[^(OneProcess|MicrokernelLikeArchitecture)$]=])
    message(FATAL_ERROR "Unknown OPEN_STG_LOADER_ARCHITECTURE")
endif()

option(OPEN_STG_OPTION_USE_MCFGTHREAD "Will use mcfgthread instead of pthread。" TRUE)
option(OPEN_STG_ENABLE_MCFGTHREAD "Enable mcfgthreaad" TRUE)
option(OPEN_STG_ENABLE_XDG_DESKTOP_PORTAL "Enable xdg desktop portal(BSD/Linux)." TRUE)
option(OPEN_STG_ENABLE_DEVELOP_TOOLS "Enable develop component." FALSE)
option(OPEN_STG_ENABLE_LIBDWARF "Enable libdwarf.(Linux,BSD,Win32)." FALSE)
option(OPEN_STG_DEVELOP_TOOLS_ENABLE_LLVM_AND_CLANG "Enable llvm and clang to generate C code." TRUE)
option(OPEN_STG_OPTION_STRING_PROCESSING_AUTO "Choose by CMake script." TRUE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source.CMake/" "${CMAKE_SOURCE_DIR}")

include(Source.CMake/SetGlobalProperties.cmake)
include(Source.CMake/AddTarget.cmake)
include(Source.CMake/FindPackage.cmake)
include(GNUInstallDirs)
include(CheckFunctionExists)
include(CheckIncludeFile)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/include")
    file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/include")
endif()

if("${CMAKE_C_COMPILER_ID}" MATCHES "^MSVC$")
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props" "${CMAKE_BINARY_DIR}")
endif()

if("${OPEN_STG_ENABLE_DEVELOP_TOOLS}" AND (NOT "${OPEN_STG_DEVELOP_TOOLS_C_CODE_GENERATOR}" MATCHES [=[^(CLANG|STRING_CONNECT)]=]))
    message(WARNING "Invalid OPEN_STG_DEVELOP_TOOLS_C_CODE_GENERATOR:${OPEN_STG_DEVELOP_TOOLS_C_CODE_GENERATOR}")
    set(OPEN_STG_ENABLE_DEVELOP_TOOLS FALSE)
endif()

message(STATUS "OPEN_STG_OPTION_USE_MCFGTHREAD:${OPEN_STG_OPTION_USE_MCFGTHREAD}")
message(STATUS "OPEN_STG_OPTION_USE_SDL3_CLOCK:${OPEN_STG_OPTION_USE_SDL3_CLOCK}")
message(STATUS "OPEN_STG_ENABLE_DEVELOP_TOOLS:${OPEN_STG_ENABLE_DEVELOP_TOOLS}")
message(STATUS "OPEN_STG_DEVELOP_TOOLS_C_CODE_GENERATOR:${OPEN_STG_DEVELOP_TOOLS_C_CODE_GENERATOR} (CLANG,STRING_CONNECT)")
message(STATUS "OPEN_STG_OPTION_STRING_PROCESSING_AUTO:${OPEN_STG_OPTION_STRING_PROCESSING_AUTO}")

add_target(
    Shared
    TARGET_TYPE INTERFACE
    LINK_DEPENDS
        INTERFACE
            ICU::data
            ICU::i18n
            ICU::io
            ${LUA_LIBRARIES}
    LINK_OPTIONS
        INTERFACE
            $<$<AND:$<BOOL:${UNIX}>,$<NOT:$<BOOL:${APPLE}>>,$<C_COMPILER_ID:GUN,Clang>,$<LINK_LANGUAGE:C,CXX>>:-rdynamic>
    COMPILE_OPTIONS
        INTERFACE
            # $<$<AND:$<C_COMPILER_ID:MSVC>,$<CONFIG:Release>,$<COMPILE_LANGUAGE:C,CXX>>:/Ox>
            $<$<COMPILE_LANGUAGE:C,CXX>:$<$<C_COMPILER_ID:MSVC>:/W4>>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:GNU,Clang>,$<COMPILE_LANGUAGE:C,CXX>>:-O> # 内存泄露检查
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CONFIG:Debug>,$<C_COMPILER_ID:Clang>>:-fsanitize=memory;-fno-omit-frame-pointer>
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
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<C_COMPILER_ID:GNU,Clang>,$<COMPILE_LANGUAGE:C,CXX>>:_FORTIFY_SOURCE=2> # 内存泄露检查
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CXX_COMPILER_ID:MSVC,Clang>>:_CRT_SECURE_NO_WARNINGS>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>>:__STDC_WANT_LIB_EXT1__=1>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CONFIG:Debug>>:_DEBUG=1>
            $<$<AND:$<COMPILE_LANGUAGE:C,CXX>,$<CONFIG:Debug>>:DEBUG=1>
    INCLUDE_DIRS
        SYSTEM
        INTERFACE
            ${LUA_INCLUDE_DIR}
)
add_target(
    Base
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PRIVATE
            Shared
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBSAFEC>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBBSD>
            $<TARGET_NAME_IF_EXISTS:libdwarf::dwarf>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBDWARF>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBPOPT>
            $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:dbghelp>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::MCFGHREAD>
            $<TARGET_NAME_IF_EXISTS:PThreads4W::PThreads4W>
            $<TARGET_NAME_IF_EXISTS:LibXml2::LibXml2>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBXML2>
            $<TARGET_NAME_IF_EXISTS:cJSON::cJSON>
            $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBCJSON>
    TARGET_PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        CXX_EXTENSIONS TRUE
        C_STANDARD 17
        C_STANDARD_REQUIRED TRUE
        C_EXTENSIONS TRUE
        POSITION_INDEPENDENT_CODE TRUE
        PREFIX "lib"
        OUTPUT_NAME "OpenStgBase"
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
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_HAS_XDG_DESKTOP_PORTAL=$<BOOL:${XDG_DESKTOP_PORTAL_FOUND}>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_HAS_LIBDWARF=$<OR:$<TARGET_EXISTS:libdwarf::dwarf>,$<TARGET_EXISTS:PkgConfig::LIBDWARF>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_STDC=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},STDC>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_LIBBSD=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},LIBBSD>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_LIBSAFEC=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},LIBSAFEC>>>
    INCLUDE_DIRS
        SYSTEM PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/Source.CAndCpp/include"
)
if(${OPEN_STG_ENABLE_DEVELOP_TOOLS})
    add_target(
        DevelopToolsLibrary
        LLVM
        TARGET_TYPE SHARED
        LINK_DEPENDS
            PRIVATE
                Shared
                $<TARGET_NAME_IF_EXISTS:LLVMCore>
                $<TARGET_NAME_IF_EXISTS:LLVMSupport>
                $<TARGET_NAME_IF_EXISTS:libclang>
                $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBPOPT>
                $<TARGET_NAME_IF_EXISTS:PkgConfig::MCFGHREAD>
                $<TARGET_NAME_IF_EXISTS:PThreads4W::PThreads4W>
                $<TARGET_NAME_IF_EXISTS:LibXml2::LibXml2>
                $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBXML2>
                $<TARGET_NAME_IF_EXISTS:cJSON::cJSON>
                $<TARGET_NAME_IF_EXISTS:PkgConfig::LIBCJSON>
            PUBLIC
                Base
        TARGET_PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS TRUE
            C_STANDARD 17
            C_STANDARD_REQUIRED TRUE
            C_EXTENSIONS TRUE
            OUTPUT_NAME "OpenStgDevelopToolsLibrary"
            PREFIX "lib"
            POSITION_INDEPENDENT_CODE TRUE
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
        INCLUDE_DIRS
            SYSTEM PUBLIC
                ${LLVM_INCLUDE_DIRS}
            PRIVATE
    )
    add_target(
        DevelopTools
        LLVM
        TARGET_TYPE EXECUTABLE
        LINK_DEPENDS
            PRIVATE
                Shared
                DevelopToolsLibrary
            PUBLIC
                Base
        TARGET_PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS TRUE
            C_STANDARD 17
            C_STANDARD_REQUIRED TRUE
            C_EXTENSIONS TRUE
            POSITION_INDEPENDENT_CODE TRUE
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
        INCLUDE_DIRS
            SYSTEM PUBLIC
                ${LLVM_INCLUDE_DIRS}
    )
endif()
add_target(
    Logic
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PRIVATE
            Shared
        PUBLIC
            Base
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
        OUTPUT_NAME "OpenStgLogic"
        PREFIX "lib"
)
add_target(
    Graphics
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PRIVATE
            SDL3::SDL3
            SDL3_ttf::SDL3_ttf
            SDL3_image::SDL3_image
            $<TARGET_NAME_IF_EXISTS:PkgConfig::XDG_DESKTOP_PORTAL>
            Shared
        PUBLIC
            Base
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
        OUTPUT_NAME "OpenStgGraphics"
        PREFIX "lib"
)
add_target(
    Network
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PRIVATE
            Shared
            $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:ws2_32>
        PUBLIC
            Base
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
        OUTPUT_NAME "OpenStgNetwork"
        PREFIX "lib"
)
add_target(
    Library
    TARGET_TYPE INTERFACE
    LINK_DEPENDS
        INTERFACE
            Base
            Graphics
            Network
            Logic
)

add_subdirectory(Source.CAndCpp/Base)
add_subdirectory(Source.CAndCpp/Logic)
add_subdirectory(Source.CAndCpp/Network)
add_subdirectory(Source.CAndCpp/Graphics)
add_subdirectory(Source.CAndCpp/DevelopTools/Library)
add_subdirectory(Source.CAndCpp/DevelopTools/Executable)

# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Rsesources")
# 如果是 Windows/MSVC，使用 copy_directory
# add_custom_command(
#     TARGET test_game POST_BUILD
#   COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory_if_different" "${RESOURCE_DIR}" "$<TARGET_FILE_DIR:test_game>/resources"
# )

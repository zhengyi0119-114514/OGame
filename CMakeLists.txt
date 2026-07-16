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

option(OPEN_STG_ENABLE_GAME_CLIENT "Enable game client support." TRUE)
option(OPEN_STG_ENABLE_GAME_SERVER "Enable game server support." TRUE)
option(OPEN_STG_ENABLE_UNIT_TESTS "Unit tests for all target." TRUE)
option(OPEN_STG_ENABLE_MCFGTHREAD "Enable mcfgthreaad" FALSE)
option(OPEN_STG_ENABLE_XDG_DESKTOP_PORTAL "Enable xdg desktop portal(BSD/Linux)." FALSE)
option(OPEN_STG_ENABLE_DEVELOP_TOOLS "Enable develop component." FALSE)
option(OPEN_STG_ENABLE_LIBDWARF "Enable libdwarf.(Linux,BSD,Win32)." FALSE)
option(OPEN_STG_ENABLE_DOWNLOAD_DEPENDENCIES "Download if dependencies miss." TRUE)
option(OPEN_STG_OPTION_STRING_PROCESSING_AUTO "Choose by CMake script." TRUE)
option(OPEN_STG_OPTION_USE_EXTERN_LINKER "Use the lld/mold/wild linker instead of the default linker." TRUE)
cmake_dependent_option(
    OPEN_STG_ENABLE_LLVM_AND_CLANG 
    "Enable llvm and clang for generate C code.(DevelopTools)"
    TRUE
    OPEN_STG_ENABLE_DEVELOP_TOOLS
    FALSE
)
cmake_dependent_option(
    OPEN_STG_ENABLE_BASE_UNIT_TESTS
    "Enable Unit testing for Base target."
    TRUE
    "OPEN_STG_ENABLE_GAME_SERVER OR OPEN_STG_ENABLE_GAME_CLIENT;OPEN_STG_ENABLE_UNIT_TESTS"
    FALSE
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source.CMake/" "${CMAKE_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Source.CMake/FindPackages/" "${CMAKE_SOURCE_DIR}")

include(SetGlobalProperties)
include(AddTarget)
include(FindPackage)
include(VcltlAndYythunks)
include(GNUInstallDirs)
include(CheckFunctionExists)
include(CheckIncludeFile)

enable_vcltl_and_yythunks()

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

add_target(
    Shared
    TARGET_TYPE INTERFACE
    LINK_DEPENDS
        INTERFACE
            ICU::data
            ICU::i18n
            ICU::io
            ${LUA_LIBRARIES}
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
target_test_and_add_compile_options(
    Shared C 
    INTERFACE
        -O
        -fsanitize=memory
        -fno-omit-frame-pointer
        -Wall
        -Wextra
        -Wno-unused-parameter
        -Wno-tautological-undefined-compare #启用编译器检查同时手动检查变量
        -Wconversion
        -Wcast-align
        -Wincompatible-function-pointer-types
        -Wincompatible-function-pointer-types-strict
        -Wincompatible-pointer-types
        /W4
        /Wall
)
target_test_and_add_compile_options(
    Shared CXX 
    INTERFACE
        -fmodules
        # -fmodules-ts
        # -stdlib=libc++
        ---precompile
        -experimental-modules-support
        -fmodule-header
        --compile-std-module
)

target_test_and_add_link_options(
    Shared C 
    INTERFACE
        -rdynamic
)
add_target(
    Base
    TARGET_TYPE SHARED
    LINK_DEPENDS
        PRIVATE
            Shared
            ${OPEN_STG_TARGET_STRING_PROCESSING_LIBRARY}
            $<$<BOOL:${OPEN_STG_TARGET_HAS_THREADS}>:${OPEN_STG_TARGET_THREADS}>
            $<$<BOOL:${OPEN_STG_TARGET_HAS_LIBDWARF}>:${OPEN_STG_TARGET_LIBDWARF}>
            $<$<BOOL:${OPEN_STG_TARGET_HAS_POPT}>:${OPEN_STG_TARGET_POPT}>
            $<$<BOOL:${OPEN_STG_TARGET_HAS_LIBXML2}>:${OPEN_STG_TARGET_LIBXML2}>
            $<$<BOOL:${OPEN_STG_TARGET_HAS_CJSON}>:${OPEN_STG_TARGET_CJSON}>
            $<$<BOOL:${OPEN_STG_TARGET_HAS_PCRE2}:${OPEN_STG_TARGET_PCRE2}>
            $<$<PLATFORM_ID:Windows,WindowsPhone,WindowsStore,MSYS>:dbghelp>
    TARGET_PROPERTIES
        CXX_STANDARD 23
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
            cxx_std_23
            cxx_constexpr
            cxx_nullptr
            c_std_17
    COMPILE_DEFINITIONS
        PRIVATE
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_STDC=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},stdc>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_LIBBSD=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},libbsd>>>
            $<$<COMPILE_LANGUAGE:C,CXX>:OPEN_STG_MACRO_USE_LIBSAFEC=$<BOOL:$<STREQUAL:${OPEN_STG_STRING_PROCESSING_LIBRARY},libsafec>>>
    INCLUDE_DIRS
        SYSTEM PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/Source.CAndCpp/include"
)
target_test_and_add_compile_options(
    Base C 
    PUBLIC 
        -fexec-charset=UTF-8
        -finput-charset=UTF-8
        /source-charset:utf-8
        /execution-charset:utf-8
        /Zc:__cplusplus
        /Zc:__STDC__
)
link_to_vcltl_and_yythunk(
    Base PUBLIC
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
                $<$<BOOL:${OPEN_STG_TARGET_HAS_POPT}>:${OPEN_STG_TARGET_POPT}>
                $<$<BOOL:${OPEN_STG_TARGET_HAS_THREADS}>:${OPEN_STG_TARGET_THREADS}>
                $<$<BOOL:${OPEN_STG_TARGET_HAS_LIBXML2}>:${OPEN_STG_TARGET_LIBXML2}>
                $<$<BOOL:${OPEN_STG_TARGET_CJSON}>:${OPEN_STG_TARGET_CJSON}>
            PUBLIC
                Base
        TARGET_PROPERTIES
            CXX_STANDARD 23
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
                cxx_std_23
                cxx_constexpr
                cxx_nullptr
                c_std_17
        COMPILE_OPTIONS
            PUBLIC
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
            CXX_STANDARD 30
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS TRUE
            C_STANDARD 17
            C_STANDARD_REQUIRED TRUE
            C_EXTENSIONS TRUE
            POSITION_INDEPENDENT_CODE TRUE
        COMPILE_FEATURES
            PUBLIC
                cxx_std_23
                cxx_constexpr
                cxx_nullptr
                c_std_17
        COMPILE_OPTIONS
        COMPILE_DEFINITIONS
        INCLUDE_DIRS
            SYSTEM PUBLIC
                ${LLVM_INCLUDE_DIRS}
    )
    add_subdirectory(Source.CAndCpp/DevelopTools/Library)
    add_subdirectory(Source.CAndCpp/DevelopTools/Executable)
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
        CXX_STANDARD 23
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
        CXX_STANDARD 23
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
if(${OPEN_STG_ENABLE_GAME_CLIENT})
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
            CXX_STANDARD 23
            CXX_STANDARD_REQUIRED TRUE
            CXX_EXTENSIONS TRUE
            C_STANDARD 17
            C_STANDARD_REQUIRED TRUE
            C_EXTENSIONS TRUE
            POSITION_INDEPENDENT_CODE TRUE
            OUTPUT_NAME "OpenStgGraphics"
            PREFIX "lib"
    )
endif()
add_subdirectory(Source.CAndCpp/Base)
add_subdirectory(Source.CAndCpp/Logic)
add_subdirectory(Source.CAndCpp/Network)
add_subdirectory(Source.CAndCpp/Graphics)

# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Rsesources")
# 如果是 Windows/MSVC，使用 copy_directory
# add_custom_command(
#     TARGET test_game POST_BUILD
#   COMMAND "${CMAKE_COMMAND}" "-E" "copy_directory_if_different" "${RESOURCE_DIR}" "$<TARGET_FILE_DIR:test_game>/resources"
# )

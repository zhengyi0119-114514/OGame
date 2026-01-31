#[[
# FindRust.cmake - Rust 工具链查找和配置模块
#
# 描述:
#   此 CMake 模块用于在 CMake 项目中查找和配置 Rust 工具链。
#   它提供了查找 Rust 相关工具（cargo、rustc、rustdoc、rustup）的功能，
#   并定义了用于构建 Rust crate 的辅助函数。
#
# 功能:
#   - 自动查找 Rust 工具链
#   - 支持不同构建类型（debug/release）
#   - 支持跨平台构建（Windows、Linux、macOS）
#   - 提供 ADD_CRATE 函数用于集成 Rust crate
#
# 用法:
#   find_package(Rust REQUIRED)
#   ADD_CRATE(my_crate [SHARED|STATIC|EXECUTABLE] SHARED)
#   target_link_libraries(YOUR_TARGET PRIVATE my_crate)
#
# 作者: zhengyi0119-114514
# 版本: 1.0
# 日期: 2025-11-29
# 许可证: MIT
#]]

cmake_minimum_required(VERSION 3.12)

include(FindPackageHandleStandardArgs)
include(CMakeParseArguments)
include(GNUInstallDirs)

macro(__RUST_FAILED_MESSAGE)
    if("${Rust_FIND_REQUIRED}")
        message(FATAL_ERROR ${ARGN})
    elseif(NOT "${Rust_FIND_QUIETLY}")
        message(WARNING ${ARGN})
    endif()
endmacro()

macro(__RUST_STATUS_MESSAGE)
    if(NOT "${Rust_FIND_QUIETLY}")
        message(STATUS ${ARGN})
    endif()
endmacro()

list(APPEND CMAKE_MESSAGE_CONTEXT "FindRust")

set(RUST_FOUND FALSE CACHE BOOL "find rustc or cargo")
set(RUST_VERSION "" CACHE STRING "rustc version")
set(RUST_CRATE_BUILD_TYPE "debug" CACHE STRING "Rust crate build type,value is one of [debug|release]")
set(RUST_CRATE_BINARY_DIR "" CACHE PATH "Cust crate build type")
set(__RUST_BUILD_OPTIONS "")

if(NOT DEFINED RUSTUP_EXECUTABLE_FILE_PATH)
    set(RUSTUP_EXECUTABLE_FILE_PATH "RUSTUP_EXECUTABLE_FILE_PATH-NOTFOUND" CACHE PATH "rustup")
    set(CARGO_EXECUTABLE_FILE_PATH "CARGO_EXECUTABLE_FILE_PATH-NOTFOUND" CACHE PATH "cargo")
    set(RUSTC_EXECUTABLE_FILE_PATH "RUSTC_EXECUTABLE_FILE_PATH-NOTFOUND" CACHE PATH "rustc")
    set(RUSTDOC_EXECUTABLE_FILE_PATH "RUSTDOC_EXECUTABLE_FILE_PATH-NOTFOUND" CACHE PATH "rustdoc")

    find_program(CARGO_EXECUTABLE_FILE_PATH NAMES "cargo" PATHS ENV PATH ENV Path)
    find_program(RUSTC_EXECUTABLE_FILE_PATH NAMES "rustc" PATHS ENV PATH ENV Path)
    find_program(RUSTDOC_EXECUTABLE_FILE_PATH NAMES "rustdoc" PATHS ENV PATH ENV Path)
    find_program(RUSTUP_EXECUTABLE_FILE_PATH NAMES "rustup" PATHS ENV PATH ENV Path)

    if(
        NOT "${CARGO_EXECUTABLE_FILE_PATH}" STREQUAL "CARGO_EXECUTABLE_FILE_PATH-NOTFOUND" AND
        NOT "${RUSTC_EXECUTABLE_FILE_PATH}" STREQUAL "RUSTC_EXECUTABLE_FILE_PATH-NOTFOUND" AND
        NOT "${RUSTDOC_EXECUTABLE_FILE_PATH}" STREQUAL "RUSTDOC_EXECUTABLE_FILE_PATH-NOTFOUND"
    )
        set(RUST_FOUND TRUE CACHE BOOL "find rustc or cargo")
    else()
        __RUST_FAILED_MESSAGE("Cargo or Rustc not found")
    endif()
endif()

set(__RUST_TARGET_DIRECTORY "${CMAKE_SOURCE_DIR}/target/" CACHE PATH "--output-dir <VALUE>")

if(NOT EXISTS "${__RUST_TARGET_DIRECTORY}")
    file(MAKE_DIRECTORY "${__RUST_TARGET_DIRECTORY}")
endif()

# Get current target
if(DEFINED RUST_TOOLCHAIN)
    set(__RUST_TOOLCHAIN "${RUST_TOOLCHAIN}")
    execute_process(
        COMMAND "${RUSTUP_EXECUTABLE_FILE_PATH}" "target" "list"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        OUTPUT_VARIABLE __RUSTUP_OUTPUT
    )

    if(NOT "${__RUST_TOOLCHAIN}" MATCHES "${__RUSTUP_OUTPUT}")
        __RUST_FAILED_MESSAGE("Unknown toolchain :${__RUST_TOOLCHAIN}")
    endif()

else()
    set(__RUST_TOOLCHAIN "")
    execute_process(
        COMMAND "${RUSTUP_EXECUTABLE_FILE_PATH}" "default"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        OUTPUT_VARIABLE __RUSTUP_OUTPUT
    )

    string(STRIP "${__RUSTUP_OUTPUT}" __RUSTUP_OUTPUT)
    string(REGEX MATCH [[^((stable)|(beta)|(nightly))-]] __RUST_TOOLCHAIN_PREFIX "${__RUSTUP_OUTPUT}")
    string(REGEX MATCH [[^((stable)|(beta)|(nightly))-[a-z0-9_]+-[a-z0-9_]+-[a-z0-9_]+(-[a-z0-9_]+)?]] __RUST_TOOLCHAIN "${__RUSTUP_OUTPUT}")
    string(REPLACE "${__RUST_TOOLCHAIN_PREFIX}" "" __RUST_TOOLCHAIN "${__RUST_TOOLCHAIN}")
endif()

list(APPEND __RUST_BUILD_OPTIONS "--target" "${__RUST_TOOLCHAIN}")

__RUST_STATUS_MESSAGE("Current rustup toolchain :${__RUST_TOOLCHAIN}")

if(NOT DEFINED RUST_CRATE_BUILD_TYPE)
    if(
        "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR
        "${CMAKE_BUILD_TYPE}" MATCHES "[Dd][Ee][Bb][Uu][Gg]"
    )
        set(RUST_CRATE_BUILD_TYPE "debug" CACHE STRING "Rust crate build type,value is a number of [debug|release]" FORCE)
    elseif(
        "${CMAKE_BUILD_TYPE}" STREQUAL "Release" OR
        "${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo" OR
        "${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel" OR
        "${CMAKE_BUILD_TYPE}" MATCHES "[Rr][Ee][Ll][Ee][Aa][Ss][Ee]"
    )
        set(RUST_CRATE_BUILD_TYPE "release" CACHE STRING "Rust crate build type,value is a number of [debug|release]" FORCE)
        list(APPEND __RUST_BUILD_OPTIONS "--release")
    endif()
endif()

set(RUST_CRATE_BINARY_DIR "${__RUST_TARGET_DIRECTORY}/${__RUST_TOOLCHAIN}/${RUST_CRATE_BUILD_TYPE}")
__RUST_STATUS_MESSAGE("Rust binary dir: ${RUST_CRATE_BINARY_DIR}")

if(
    "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsPhone" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "MSYS" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN"
)
    set(__RUST_EXECUTABLE_FILE_EXTENSION ".exe")
    set(__RUST_STATIC_LIBRARY_FILE_EXTENSION ".lib")
    set(__RUST_IMPROT_LIBRARY_FILE_EXTENSION ".dll.lib")
    set(__RUST_SHARED_LIBRARY_FILE_EXTENSION ".dll")
    set(__RUST_STATIC_LIBRARY_FILE_SUFFIX "")
    set(__RUST_SHARED_LIBRARY_FILE_SUFFIX "")

    if("${__RUST_TOOLCHAIN}" MATCHES "[Gg][Nn][Uu]")
        set(__RUST_STATIC_LIBRARY_FILE_SUFFIX "lib")
        set(__RUST_IMPROT_LIBRARY_FILE_EXTENSION ".dll.a")
    endif()
else()
    set(__RUST_EXECUTABLE_FILE_EXTENSION "") # none
    set(__RUST_STATIC_LIBRARY_FILE_EXTENSION ".a")
    set(__RUST_STATIC_LIBRARY_FILE_SUFFIX "lib")
    set(__RUST_SHARED_LIBRARY_FILE_SUFFIX "lib")

    if(
        "${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "tvOS"
    )
        set(__RUST_SHARED_LIBRARY_FILE_EXTENSION ".dylib")
    else()
        set(__RUST_SHARED_LIBRARY_FILE_EXTENSION ".so")
    endif()
endif()

function(__HANDLE_DEPENDENCIES __crate __dependencies)
    set("${__crate}_DEPENDENCIES" "")
    foreach(__dependency ${__dependencies})
        if(TARGET "${__dependency}")
            list(APPEND "${__crate}_DEPENDENCIES" $<TARGET_FILE:${__dependency}>)
        elseif("${__dependency}" MATCHES "^.+((\.dll.a)|(\.so)|(\.a)|(\.dylib)|(\.lib)){1}$")
            list(APPEND "${__crate}_DEPENDENCIES" "${__dependency}")
        endif()
    endforeach()
    string(REPLACE ";" "\n" "${__crate}_DEPENDENCIES_FILE_CONTENT" "${${__crate}_DEPENDENCIES}")

    file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/${__crate}_$<LOWER_CASE:$<CONFIG>>_dependencies.txt" CONTENT "${${__crate}_DEPENDENCIES_FILE_CONTENT}")
    file(GENERATE OUTPUT "${RUST_CRATE_BINARY_DIR}/${__crate}_$<LOWER_CASE:$<CONFIG>>_dependencies.txt" CONTENT "${${__crate}_DEPENDENCIES_FILE_CONTENT}")
    set("${__crate}_DEPENDENCIES" "${${__crate}_DEPENDENCIES}" CACHE STRING "Crate dependencies" FORCE)
endfunction()

function(__ADD_EXECUTABLE_CRATE __crate __source_dir __dependencies)
    # Create imported executable target that depends on the build target
    set(
        "${__crate}_BINARY_FILE" "${RUST_CRATE_BINARY_DIR}/${__crate}${__RUST_EXECUTABLE_FILE_EXTENSION}"
        CACHE FILEPATH "Rust crate binary file" FORCE
    )
    set(
        __COMMAND "${CARGO_EXECUTABLE_FILE_PATH}" "build" "--target-dir" "${__RUST_TARGET_DIRECTORY}"
        ${__RUST_BUILD_OPTIONS} "-p" "${__crate}" ${ARGN}
    )
    # Create a custom target for building the Rust crate
    add_custom_target("_${__crate}_build"
        COMMAND ${__COMMAND}
        WORKING_DIRECTORY "${__source_dir}"
        DEPENDS ${__dependencies}
        COMMENT "Building Rust bin crate \"${__crate}\""
    )
    add_custom_target("${__crate}" ALL
        COMMAND ${__COMMAND}
        DEPENDS "_${__crate}_build" ${__dependencies}
        WORKING_DIRECTORY "${RUST_CRATE_BINARY_DIR}"
    )
endfunction()

function(__ADD_STATIC_LIBRARY_CRATE __crate __source_dir __dependencies)
    set("${__crate}_BINARY_FILE" "${RUST_CRATE_BINARY_DIR}/${__RUST_STATIC_LIBRARY_FILE_SUFFIX}${__crate}${__RUST_STATIC_LIBRARY_FILE_EXTENSION}"
        CACHE FILEPATH "Rust crate binary file" FORCE
    )
    set(__COMMAND
        "${CARGO_EXECUTABLE_FILE_PATH}" "build" "-p" "${__crate}" ${__RUST_BUILD_OPTIONS} "--target-dir" "${__RUST_TARGET_DIRECTORY}" ${ARGN}
    )
    add_custom_command(
        OUTPUT ${${__crate}_BINARY_FILE}
        COMMAND ${__COMMAND}
        WORKING_DIRECTORY "${__source_dir}"
        DEPENDS ${__dependencies}
        COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
    )
    add_custom_target(
        "_${__crate}_build" ALL
        COMMAND ${__COMMAND}
        DEPENDS ${${__crate}_BINARY_FILE} ${__dependencies}
        WORKING_DIRECTORY "${__source_dir}"
        COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
    )
    add_library("${__crate}" SHARED IMPORTED GLOBAL)
    set_target_properties("${__crate}"
        PROPERTIES
        IMPORTED_LOCATION "${${__crate}_BINARY_FILE}"
    )
endfunction()

function(__ADD_SHARED_LIBRARY_CRATE __crate __source_dir __dependencies)
    if(
        "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsPhone" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "MSYS" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN"
    )
        set("${__crate}_IMPORTED_LIBRARY" "${RUST_CRATE_BINARY_DIR}/${__RUST_STATIC_LIBRARY_FILE_SUFFIX}${__crate}${__RUST_IMPROT_LIBRARY_FILE_EXTENSION}" CACHE FILEPATH "lib<DLL_NAME>.dll.a or <DLL_NAME>.dll.lib" FORCE)
        set("${__crate}_DLL_FILE" "${RUST_CRATE_BINARY_DIR}/${__RUST_SHARED_LIBRARY_FILE_SUFFIX}${__crate}${__RUST_SHARED_LIBRARY_FILE_EXTENSION}" CACHE FILEPATH "<DLL_NAME>.dll" FORCE)
        set("${__crate}_BINARY_FILE" "${${__crate}_IMPORTED_LIBRARY}" "${${__crate}_DLL_FILE}" CACHE FILEPATH "Rust crate binary file" FORCE)
        set("${__crate}_PDB_FILE" "${RUST_CRATE_BINARY_DIR}/${__RUST_SHARED_LIBRARY_FILE_SUFFIX}${__crate}.pdb" CACHE FILEPATH "<DLL_NAME>.pdb" FORCE)

        set(__COMMAND
            "${CARGO_EXECUTABLE_FILE_PATH}" "build" "-p" "${__crate}" ${__RUST_BUILD_OPTIONS} "--target-dir" "${__RUST_TARGET_DIRECTORY}" ${ARGN}
        )
        add_custom_command(
            OUTPUT ${${__crate}_BINARY_FILE}
            COMMAND ${__COMMAND}
            WORKING_DIRECTORY "${__source_dir}"
            DEPENDS ${__dependencies}
            COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
        )
        add_custom_target(
            "_${__crate}_build" ALL
            COMMAND ${__COMMAND}
            DEPENDS ${${__crate}_BINARY_FILE} ${__dependencies}
            WORKING_DIRECTORY "${__source_dir}"
            COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
        )
        add_library("${__crate}" SHARED IMPORTED GLOBAL)
        set_target_properties("${__crate}"
            PROPERTIES
            IMPORTED_LOCATION "${${__crate}_DLL_FILE}"
            IMPORTED_IMPLIB "${${__crate}_IMPORTED_LIBRARY}"
        )
    else()
        set(
            "${__crate}_BINARY_FILE" "${RUST_CRATE_BINARY_DIR}/${__RUST_SHARED_LIBRARY_FILE_SUFFIX}${__crate}${__RUST_SHARED_LIBRARY_FILE_EXTENSION}"
            CACHE FILEPATH "Rust crate binary file" FORCE
        )
        set(__COMMAND
            "${CARGO_EXECUTABLE_FILE_PATH}" "build" "-p" "${__crate}" ${__RUST_BUILD_OPTIONS} "--target-dir" "${__RUST_TARGET_DIRECTORY}" ${ARGN}
        )
        add_custom_command(
            OUTPUT "${${__crate}_BINARY_FILE}"
            COMMAND ${__COMMAND}
            WORKING_DIRECTORY "${__source_dir}"
            DEPENDS ${__dependencies}
            COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
        )
        add_custom_target("_${__crate}_build" ALL
            COMMAND ${__COMMAND}
            DEPENDS ${${__crate}_BINARY_FILE}
            WORKING_DIRECTORY "${__source_dir}"
            DEPENDS ${__dependencies}
            COMMENT "Building rust crate ${__crate} target_dir:${__RUST_TARGET_DIRECTORY}"
        )
        add_library("${__crate}" SHARED IMPORTED GLOBAL)
        set_target_properties("${__crate}"
            PROPERTIES
            IMPORTED_LOCATION "${${__crate}_BINARY_FILE}"
        )
    endif()
endfunction()

# import rust crate as a target
function(ADD_CRATE __crate)
    set("${__crate}_BINARY_FILE" "" CACHE FILEPATH "Rust crate binary file" FORCE)

    # set("${__crate}_DEPENDS" "" CACHE STRINGS "Rust crate dependencies")
    cmake_parse_arguments(__CRATE
        "OFFLINE;LOCKED" # Options
        "SOURCE_DIRECTORY;CRATE_TYPE" # One value keywords
        "DEPENDS" "ADDITIONAL_PARAMETERS" # Multi value keywords
        ${ARGV}
    )

    if(
        "${__CRATE_SOURCE_DIRECTORY}" STREQUAL "" OR
        NOT DEFINED __CRATE_SOURCE_DIRECTORY
    )
        set(__SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    else()
        set(__SOURCE_DIR "${__CRATE_SOURCE_DIRECTORY}")
    endif()
    __HANDLE_DEPENDENCIES("${__crate}" "${__CRATE_DEPENDS}")
    if(
        "${__CRATE_CRATE_TYPE}" STREQUAL "cdylib" OR
        "${__CRATE_CRATE_TYPE}" STREQUAL "SHARED"
    )
        __ADD_SHARED_LIBRARY_CRATE("${__crate}" "${__SOURCE_DIR}" "${__CRATE_DEPENDS}" ${__CRATE_ADDITIONAL_PARAMETERS})
    elseif(
        "${__CRATE_CRATE_TYPE}" STREQUAL "staticlib" OR
        "${__CRATE_CRATE_TYPE}" STREQUAL "STATIC"
    )
        __ADD_STATIC_LIBRARY_CRATE("${__crate}" "${__SOURCE_DIR}" "${__CRATE_DEPENDS}" ${__CRATE_ADDITIONAL_PARAMETERS})
    elseif(
        "${__CRATE_CRATE_TYPE}" STREQUAL "bin" OR
        "${__CRATE_CRATE_TYPE}" STREQUAL "exe" OR
        "${__CRATE_CRATE_TYPE}" STREQUAL "EXECUTABLE"
    )
        __ADD_EXECUTABLE_CRATE("${__crate}" "${__SOURCE_DIR}" "${__CRATE_DEPENDS}" ${__CRATE_ADDITIONAL_PARAMETERS})
    else()
        __RUST_FAILED_MESSAGE("Unsupported CRATE_TYPE :${__CRATE_CRATE_TYPE},it must be one of [cdylib|SHARED|staticlib|STATIC|bin|EXECUTABLE]")
    endif()
endfunction()

function(TARGET_LINK_SHARED_CRATE __target)
    cmake_parse_arguments(__CRATE
        "" # Options
        "" # One value keyword
        "PUBLIC" "PRIVATE" # Multi value keywords
        ${ARGV}
    )
    target_link_libraries(
        "${__target}"
        PUBLIC ${__CRATE_PUBLIC}
        PRIVATE ${__CRATE_PRIVATE}
    )

    if("${CMAKE_SYSTEM_NAME}" MATCHES "Windows" OR
        "${CMAKE_SYSTEM_NAME}" STREQUAL "MSYS")
        foreach(__crate ${__CRATE_PUBLIC} ${__CRATE_PRIVATE})
            add_custom_command(TARGET "${__target}" POST_BUILD
                COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${${__crate}_DLL_FILE}" "$<TARGET_FILE_DIR:${__target}>"
                COMMAND
                $<
                    $<AND:
                        $<CONFIG:Debug>,
                        $<PLATFORM_ID:Windows,WindowsStore,WindowsPhone>,
                        $<OR:
                            $<STREQUAL:${__RUST_TOOLCHAIN},x86_64-pc-windows-msvc>,
                            $<STREQUAL:${__RUST_TOOLCHAIN},i686-pc-windows-msvc>,
                            $<STREQUAL:${__RUST_TOOLCHAIN},aarch64-pc-windows-msvc>
                        >
                    >
                :${CMAKE_COMMAND};-E;copy_if_different;${${__crate}_PDB_FILE};$<TARGET_FILE_DIR:${__target}>>
            )
        endforeach()
    endif()
endfunction()

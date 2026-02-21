#[=[
    LICENSE: MIT
#]=]
cmake_minimum_required (VERSION 3.20)

include (FindPackageHandleStandardArgs)
include (CMakeParseArguments)
include (GNUInstallDirs)
include (AddTarget)

macro (__RUST_FAILED_MESSAGE)
    message (FATAL_ERROR ${ARGN})
endmacro ()

macro (__RUST_STATUS_MESSAGE __is_quiet)
    if (NOT "${Rust_FIND_QUIETLY}" AND NOT "${__is_quiet}")
        message (STATUS ${ARGN})
    endif ()
endmacro ()

macro (__RUST_WARNING_MESSAGE)
    if (NOT "${Rust_FIND_QUIETLY}")
        message (WARNING ${ARGN})
    endif ()
endmacro ()

set (RUST_FOUND TRUE CACHE BOOL "find rustc or cargo")
set (RUST_VERSION "" CACHE STRING "rustc version")
set (__RUST_IMPORTABLE_CRATE_TYPE_REGEX "((bin)|(lib)|(rlib)|(dylib)|(cdylib)|(staticlib))")

if (NOT DEFINED RUST_RUSTUP_EXECUTABLE)
    set (RUST_RUSTUP_EXECUTABLE "RUST_RUSTUP_EXECUTABLE-NOTFOUND" CACHE PATH "rustup")
    set (RUST_CARGO_EXECUTABLE "RUST_CARGO_EXECUTABLE-NOTFOUND" CACHE PATH "cargo")
    set (RUST_RUSTC_EXECUTABLE "RUST_RUSTC_EXECUTABLE-NOTFOUND" CACHE PATH "rustc")
    set (RUST_RUSTDOC_EXECUTABLE "RUST_RUSTDOC_EXECUTABLE-NOTFOUND" CACHE PATH "rustdoc")
    set (RUST_CARGO_ZIGBUILD_EXECUTABLE "RUST_CARGO_ZIGBUILD_EXECUTABLE-NOTFOUND" CACHE PATH "cargo-zigbuild")
    set (RUST_ZIG_EXECUTABLE "RUST_ZIG_EXECUTABLE" CACHE PATH "zig")

    find_program (RUST_CARGO_EXECUTABLE NAMES "cargo" PATHS ENV PATH ENV Path)
    find_program (RUST_RUSTC_EXECUTABLE NAMES "rustc" PATHS ENV PATH ENV Path)
    find_program (RUST_RUSTDOC_EXECUTABLE NAMES "rustdoc" PATHS ENV PATH ENV Path)
    find_program (RUST_RUSTUP_EXECUTABLE NAMES "rustup" PATHS ENV PATH ENV Path)
    find_program (RUST_CARGO_ZIGBUILD_EXECUTABLE NAMES "cargo-zigbuild" PATHS ENV PATH ENV Path)

    if (
        (NOT "${RUST_CARGO_EXECUTABLE}") AND
        (NOT "${RUST_RUSTC_EXECUTABLE}") AND
        (NOT "${RUST_RUSTDOC_EXECUTABLE}")
    )
        set (RUST_FOUND TRUE CACHE BOOL "find rustc or cargo")
    else ()
        __RUST_FAILED_MESSAGE ("Cargo or Rustc not found")
    endif ()

    if (
        (NOT "${RUST_CARGO_ZIGBUILD_EXECUTABLE}") AND
        (NOT "${RUST_ZIG_EXECUTABLE}")
    )
        set (RUST_CARGO_ZIGBUILD_FOUND TRUE)
    else ()
        set (RUST_CARGO_ZIGBUILD_FOUND FALSE)
    endif ()
endif ()

# Get current target
if (DEFINED RUST_TOOLCHAIN)
    set (__RUST_TOOLCHAIN "${RUST_TOOLCHAIN}")
    execute_process (
        COMMAND "${RUST_RUSTUP_EXECUTABLE}" "target" "list"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        OUTPUT_VARIABLE __RUSTUP_OUTPUT
    )

    if (NOT "${__RUST_TOOLCHAIN}" MATCHES "${__RUSTUP_OUTPUT}")
        __RUST_FAILED_MESSAGE ("Unknown toolchain :${__RUST_TOOLCHAIN}")
    endif ()

    cmake_path (APPEND RUST_CRATE_BINARY_DIR "${__RUST_TOOLCHAIN}")
    set (__RUST_IS_DEFINED_TOOLCHAIN TRUE)
else ()
    set (__RUST_TOOLCHAIN "")
    execute_process (
        COMMAND "${RUST_RUSTUP_EXECUTABLE}" "default"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        OUTPUT_VARIABLE __RUSTUP_OUTPUT
    )

    string (STRIP "${__RUSTUP_OUTPUT}" __RUSTUP_OUTPUT)
    string (REGEX MATCH [[^((stable)|(beta)|(nightly))-]] __RUST_TOOLCHAIN_PREFIX "${__RUSTUP_OUTPUT}")
    string (REGEX MATCH [[^((stable)|(beta)|(nightly))-[a-z0-9_]+-[a-z0-9_]+-[a-z0-9_]+(-[a-z0-9_]+)?]] __RUST_TOOLCHAIN "${__RUSTUP_OUTPUT}")
    string (REPLACE "${__RUST_TOOLCHAIN_PREFIX}" "" __RUST_TOOLCHAIN "${__RUST_TOOLCHAIN}")
    set (__RUST_IS_DEFINED_TOOLCHAIN FALSE)
    set (RUST_TOOLCHAIN "${__RUST_TOOLCHAIN}")
endif ()

__RUST_STATUS_MESSAGE (FALSE "Current rustup toolchain :${__RUST_TOOLCHAIN}")

if ("${RUST_VERSION}" STREQUAL "")
    execute_process (
        COMMAND "${RUST_CARGO_EXECUTABLE}" "--help"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        OUTPUT_VARIABLE __CARGO_OUTPUT
    )
    string (STRIP "${__CARGO_OUTPUT}" __CARGO_OUTPUT)
    string (REGEX MATCH [=[[0-9]+\.[0-9]+\.[0-9]+]=] __RUSTC_VERSION "${__CARGO_OUTPUT}")
    set (RUST_VERSION "${__RUSTC_VERSION}" CACHE STRING "rustc version" FORCE)
endif ()


cmake_path (APPEND RUST_CRATE_BINARY_DIR "${RUST_CRATE_BUILD_TYPE}")

if (
    "${RUST_TOOLCHAIN}" MATCHES "windows"
)
    set (__RUST_BIN_SUFFIX ".exe")
    set (__RUST_STATICLIB_PREFIX "")
    set (__RUST_STATICLIB_SUFFIX ".lib")
    set (__RUST_IMPROT_LIBRARY_FILE_PREFIX "")
    set (__RUST_IMPROT_LIBRARY_FILE_SUFFIX ".dll.lib")
    set (__RUST_DYLIB_PREFIX "")
    set (__RUST_DYLIB_SUFFIX ".dll")

    if ("${RUST_TOOLCHAIN}" MATCHES "[Gg][Nn][Uu]")
        set (__RUST_STATICLIB_PREFIX "lib")
        set (__RUST_IMPROT_LIBRARY_FILE_PREFIX "lib")
        set (__RUST_IMPROT_LIBRARY_FILE_SUFFIX ".dll.a")
    endif ()
else ()
    set (__RUST_BIN_SUFFIX "") # none
    set (__RUST_STATICLIB_SUFFIX ".a")
    set (__RUST_STATICLIB_PREFIX "lib")
    set (__RUST_DYLIB_PREFIX "lib")

    if (
        "${RUST_TOOLCHAIN}" MATCHES "apple"
    )
        set (__RUST_DYLIB_SUFFIX ".dylib")
    else ()
        set (__RUST_DYLIB_SUFFIX ".so")
    endif ()
endif ()

set (__RUST_RLIB_PREFIX "lib")
set (__RUST_RLIB_SUFFIX ".rlib")

function (__RUST_HANDLE_AND_EXPORT __crate __binary_dir)
    cmake_parse_arguments (
        PARSE_ARGV 2
        __argument
        ""
        ""
        "DEPENDS"
    )

    # message(NOTICE "${__file_path}")
    set (__file_content)
    set (__depends "${__argument_DEPENDS}")
    set (__flags "${__argument_FLAGS}")

    foreach (__depend IN LISTS __depends)
        if (TARGET "${__depend}" AND NOT DEFINED "${__depend}_RUST_TAG")
            get_target_property (__type "${__depend}" TYPE)
            get_target_property (__link_options "${__depend}" LINK_OPTIONS)

            if ("${__type}" MATCHES "^((STATIC_LIBRARY)|(SHARED_LIBRARY))$")
                string (APPEND __file_content "CONTENT|${__link_options}\n")
                string (APPEND __file_content "LINK_LIBRARY|BASE_NAME=$<TARGET_LINKER_FILE_BASE_NAME:${__depend}>|DIR=$<TARGET_LINKER_FILE_DIR:${__depend}>|FILE=$<TARGET_FILE:${__depend}>\n")
            else ()
            endif ()
        elseif ("${__depend}" MATCHES [=[.+\.((lib)|(a))$]=])
            string (APPEND __file_content "LINK_FILE|${__depend}\n")
        endif ()
    endforeach ()

    if (NOT "${__file_content}" STREQUAL "")
        file (GENERATE OUTPUT "${__binary_dir}/Config-${__crate}.txt" CONTENT "${__file_content}")
    endif ()
endfunction ()

function (ADD_CRATE __crate_name)
    set (__ADD_CRATE_OPTIONS
        "IMPORTED_TARGET"
        "QUIET"
        "ZIGBUILD"
    )
    set (__ADD_CRATE_ONE_VALUE_KEYWORD
        "MANIFEST_FILE" # - */Cargo.toml
        "SOURCE_DIR" # - exist <dir>/Cargo.toml
        "BINARY_DIR" # - --target-dir
        "JOBS" # --jobs 如果为空，将自动设置为逻辑CPU核数
        "JOB_POOL"
        "TARGET_ALIAS_NAME" # -
        "IMPORTED_TARGET_NAMESPACE" # -
        "DEFAULT_TYPE"
    )
    set (__ADD_CRATE_MULTI_VALUE_KEYWORD
        "DEPENDS"
        "CRATE_TYPE"
        "CARGO_OPTIONS" # 将传导至cargo build命令，可以使用生成器表达式
    )
    cmake_parse_arguments (
        PARSE_ARGV 1
        __argument
        "${__ADD_CRATE_OPTIONS}"
        "${__ADD_CRATE_ONE_VALUE_KEYWORD}"
        "${__ADD_CRATE_MULTI_VALUE_KEYWORD}"
    )
    set (__crate_is_imported_target "${__argument_IMPORTED_TARGET}")
    set (__crate_is_quiet "${__argument_QUIET}")
    set (__crate_source_dir "${__argument_SOURCE_DIR}")
    set (__crate_target_dir "${__argument_BINARY_DIR}")
    set (__crate_binary_files "")
    set (__crate_binary_dir)
    set (__crate_manifest_file "${__argument_MANIFEST_FILE}")

    if (NOT "${__crate_source_dir}" STREQUAL "")
        file (REAL_PATH "${__crate_source_dir}" __crate_source_dir)
    endif ()

    if (NOT "${__crate_target_dir}" STREQUAL "")
        file (REAL_PATH "${__crate_target_dir}" __crate_target_dir)
    endif ()

    if (NOT "${__crate_manifest_file}" STREQUAL "")
        file (REAL_PATH "${__crate_manifest_file}" __crate_manifest_file)
    endif ()

    set (__crate_jobs "${__argument_JOBS}")
    set (__crate_build_command "build")
    set (__crate_target_alias_name "${__argument_TARGET_ALIAS_NAME}")
    set (__crate_target_namespace "${__argument_IMPORTED_TARGET_NAMESPACE}")
    set (__crate_depends "${__argument_DEPENDS}")
    set (__crate_linkable_depends)
    set (__crate_rust_depend)
    set (__crate_crate_type "${__argument_CRATE_TYPE}")
    set (__crate_default_type "${__argument_DEFAULT_TYPE}")
    set (__crate_rustc_flag)
    set (__crate_build_options)
    set (__crate_job_pool "${__argument_JOB_POOL}")
    set (__copy_commands)
    set (__job_pool_options)

    if ("${__argument_ZIG_BUILD}" AND "${RUST_CARGO_ZIGBUILD_FOUND}")
        set (__crate_build_command "zigbuild")
    endif ()

    # ##### 验证SOURCE_DIR与MANIFEST_FILE是否冲突
    if ("${__crate_manifest_file}" MATCHES [=[[Cc][Aa][Rr][Gg][Oo]\.[Tt][Oo][Mm][Ll]$]=])
    endif ()

    if ("${__crate_source_dir}" STREQUAL "" AND "${__crate_manifest_file}" STREQUAL "")
        __RUST_FAILED_MESSAGE ("SOURCE_DIR or MANIFEST_FILE are not set.")
    endif ()

    # SOURCE_DIR 为
    if ((NOT "${__crate_source_dir}" STREQUAL "") AND(NOT "${__crate_manifest_file}" STREQUAL ""))
        cmake_path (APPEND __crate_source_dir "Cargo.toml" OUTPUT_VARIABLE __crate_source_manifest_file)
        cmake_path (COMPARE "${__crate_manifest_file}" EQUAL "${__crate_source_manifest_file}" __is_same)

        if (NOT ${__is_same})
            __RUST_FAILED_MESSAGE ("Crate:'${__crate_name}' Multiple possible MANIFEST_FILE.")
        endif ()
    endif ()

    if (NOT "${__crate_source_manifest_file}" STREQUAL "")
        set (__crate_manifest_file "${__crate_source_manifest_file}")
    endif ()

    cmake_path (GET __crate_manifest_file PARENT_PATH __crate_source_dir)

    # ##### 自动设置 BINARY_DIR
    if ("${__crate_target_dir}" STREQUAL "")
        cmake_path (APPEND __crate_source_dir "target" OUTPUT_VARIABLE __crate_target_dir)
    endif ()

    # string (APPEND __crate_binary_dir
    # "${__crate_target_dir}"
    # # $<$<BOOL:${__RUST_IS_DEFINED_TOOLCHAIN}>:/${__RUST_TOOLCHAIN}>
    # # $<IF:$<CONFIG:Release,RelWithDebInfo,MinSizeRel>,/release,/debug>
    # )
    set (__crate_binary_dir "${__crate_target_dir}")

    if (${__RUST_IS_DEFINED_TOOLCHAIN})
        cmake_path (APPEND __crate_binary_dir "${__RUST_TOOLCHAIN}")
    endif ()

    cmake_path (APPEND __crate_binary_dir "debug" OUTPUT_VARIABLE __crate_binary_dir_debug)
    cmake_path (APPEND __crate_binary_dir "release" OUTPUT_VARIABLE __crate_binary_dir_release)
    string (APPEND __crate_binary_dir $<IF:$<CONFIG:Release,RelWithDebInfo,MinSizeRel>,/release,/debug>)

    # ##### 自动设置 JOB
    if (NOT "${__crate_jobs}" MATCHES "[0-9]+")
        cmake_host_system_information (RESULT __crate_jobs QUERY NUMBER_OF_LOGICAL_CORES)
    endif ()

    # ##### 处理 DEFAULT_TYPE 和 CRATE_TYPE
    # #### 处理CRATE_TYPE
    if ("${__crate_crate_type}" STREQUAL "")
        __RUST_FAILED_MESSAGE ("CRATE_TYPE is required.")
    endif ()

    string (REGEX REPLACE [=[((")|(')|( )){1}]=] "" __crate_crate_type "${__crate_crate_type}")
    string (REGEX REPLACE [=[((\|)|(,)|(:)|(;)){1}]=] ";" __crate_crate_type "${__crate_crate_type}")
    string (REGEX REPLACE [=[(LINKABLE_)?((SHARED(_LIBRARY)?)|(DYNAMIC((_LINK)?_LIBRARY)?)|(DLL))]=] "cdylib" __crate_crate_type "${__crate_crate_type}")
    string (REGEX REPLACE [=[(LINKABLE_)?((STATIC((_)?LIB(RARY)?)?)|(ARCHIVE))]=] "staticlib" __crate_crate_type "${__crate_crate_type}")
    string (REGEX REPLACE [=[(EXE(CUTABLE)?){1}]=] "bin" __crate_crate_type "${__crate_crate_type}")
    string (REGEX REPLACE [=[(LINKABLE_)?((SHARED(_LIBRARY)?)|(DYNAMIC((_LINK)?_LIBRARY)?)|(DLL))]=] "cdylib" __crate_default_type "${__crate_default_type}")
    string (REGEX REPLACE [=[(LINKABLE_)?((STATIC((_)?LIB(RARY)?)?)|(ARCHIVE))]=] "staticlib" __crate_default_type "${__crate_default_type}")

    foreach (__type IN ITEMS "staticlib" "cdylib")
        string (REGEX MATCHALL "${__type}" __types "${__crate_crate_type}")
        list (LENGTH __types __type_length)

        if (${__type_length} GREATER 1)
            __RUST_FAILED_MESSAGE ("Multiple ${__type}.")
        endif ()
    endforeach ()

    # ### 处理 DEFAULT_TYPE
    if ("${__crate_crate_type}" MATCHES [=[((cdylib)|(staticlib))]=])
        if ("${__crate_default_type}" STREQUAL "")
            if ("${__crate_crate_type}" MATCHES [=[cdylib]=])
                set (__crate_default_type "cdylib")
            else ()
                set (__crate_default_type "staticlib")
            endif ()
        else ()
            if (
                NOT(("${__crate_default_type}" MATCHES "^${__RUST_IMPORTABLE_CRATE_TYPE_REGEX}$")
                AND("${__crate_default_type}" IN_LIST __crate_crate_type))
            )
                __RUST_FAILED_MESSAGE ("Invalid DEFAULT_TYPE.")
            endif ()
        endif ()
    endif ()

    # ### 处理冲突选项
    # ## proc-macro和other
    if ("${__crate_crate_type}" MATCHES [=[proc-macro]=])
        __RUST_FAILED_MESSAGE ("'proc-macro' is not importable.")
    endif ()

    # ## 检查子项
    foreach (__type IN LISTS __crate_crate_type)
        if (NOT "${__type}" MATCHES "^${__RUST_IMPORTABLE_CRATE_TYPE_REGEX}$")
            __RUST_FAILED_MESSAGE ("Unknown crate type '${__type}'.")
        endif ()
    endforeach ()

    # ## bin和lib
    if ("${__crate_crate_type}" MATCHES [=[bin]=] AND "${__crate_crate_type}" MATCHES [=[((lib)|(proc-macro))]=])
        __RUST_FAILED_MESSAGE ("Cannot mix `bin` crate type with others")
    endif ()

    # ## cdylib和dylib
    string (REGEX MATCHALL [=[((^dylib)|(;dylib)|(cdylib)){1}]=] __dylibs "${__crate_crate_type}")
    list (LENGTH __dylibs __dylib_number)

    if (${__dylib_number} GREATER 1)
        __RUST_FAILED_MESSAGE ("Multiple dylibs.")
    endif ()

    # ##### 设置IMPORTED_TARGET_NAMESPACE
    if ("${__crate_target_namespace}" STREQUAL "")
        set (__crate_target_namespace "RustCargo")
    endif ()

    # ##### 设置构建指令
    list (APPEND __crate_build_options "--package" "${__crate_name}")
    list (APPEND __crate_build_options $<$<CONFIG:Release,RelWithDebInfo,MinSizeRel>:--release>)
    list (APPEND __crate_build_options "--jobs" "${__crate_jobs}")
    list (APPEND __crate_build_options "--manifest-path" "${__crate_manifest_file}")
    list (APPEND __crate_build_options "--target-dir" "${__crate_target_dir}")
    list (APPEND __crate_build_options $<$<BOOL:${__RUST_IS_DEFINED_TOOLCHAIN}>:--target> $<$<BOOL:${__RUST_IS_DEFINED_TOOLCHAIN}>:${RUST_TOOLCHAIN}>)
    list (APPEND __crate_build_options ${__argument_CARGO_OPTIONS})

    # ##### 处理((艾司唑仑片)|(奥氮平片)|(盐酸文拉法辛缓释片)|(盐酸氟西汀胶囊)){1}

    # ##### 处理DEPENDS
    foreach (__depend IN LISTS __crate_depends)
        if (DEFINED "${__depend}_RUST_TAG")
            list (APPEND __crate_rust_depend "CargoBuild_${__depend}")
        else ()
            list (APPEND __crate_linkable_depends "${__depend}")
        endif ()
    endforeach ()

    # ##### 处理JOB_POOL
    if (("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "4.20") AND(NOT "${__crate_job_pool}" STREQUAL "3.15"))
        list (APPEND __job_pool_options JOB_POOL ${__crate_job_pool})
    endif ()

    # ##### 生成BinaryFiles
    foreach (__type IN LISTS __crate_crate_type)
        string (STRIP "${__type}" __type)

        if ("${__type}" MATCHES [=[^bin$]=])
            set (__crate_binary_files_exe "${__crate_binary_dir}/${__crate_name}${__RUST_BIN_SUFFIX}")
            set (__crate_binary_files_exe_copy "${CMAKE_CURRENT_BINARY_DIR}/${__crate_name}${__RUST_BIN_SUFFIX}")
            list (APPEND __copy_commands COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${__crate_binary_files_exe}" "${__crate_binary_files_exe_copy}")
            list (APPEND __crate_binary_files "${__crate_binary_files_exe_copy}")

            if (${__crate_is_imported_target})
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Add executable target \"${__crate_target_namespace}::${__crate_name}\"")
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Binary file:${__crate_binary_files_exe_copy}")
                add_executable ("${__crate_target_namespace}::${__crate_name}" IMPORTED GLOBAL)
                set_target_properties ("${__crate_target_namespace}::${__crate_name}"
                    PROPERTIES
                        IMPORTED_LOCATION "${__crate_binary_files_exe_copy}"
                )
            endif ()
        elseif ("${__type}" MATCHES [=[^((dylib)|(cdylib))$]=])
            set (__crate_has_dynamic TRUE)
            set (__crate_binary_files_dylib "${__crate_binary_dir}/${__RUST_DYLIB_PREFIX}${__crate_name}${__RUST_DYLIB_SUFFIX}")
            set (__crate_binary_files_dylib_copy "${CMAKE_CURRENT_BINARY_DIR}/${__RUST_DYLIB_PREFIX}${__crate_name}${__RUST_DYLIB_SUFFIX}")
            list (APPEND __copy_commands COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${__crate_binary_files_dylib}" "${__crate_binary_files_dylib_copy}")
            list (APPEND __crate_binary_files "${__crate_binary_files_dylib_copy}")

            if ("${__type}" MATCHES [=[^cdylib$]=] AND ${__crate_is_imported_target})
                set (__crate_is_dynamic_linkable TRUE)

                if ("${__RUST_TOOLCHAIN}" MATCHES "windows")
                    set (__crate_binary_files_dylib_implib "${__crate_binary_dir}/${__RUST_IMPROT_LIBRARY_FILE_PREFIX}${__crate_name}${__RUST_IMPROT_LIBRARY_FILE_SUFFIX}")
                    set (__crate_binary_files_dylib_implib_copy "${CMAKE_CURRENT_BINARY_DIR}/${__RUST_IMPROT_LIBRARY_FILE_PREFIX}${__crate_name}${__RUST_IMPROT_LIBRARY_FILE_SUFFIX}")
                    list (APPEND __crate_binary_files "${__crate_binary_files_dylib_implib_copy}")
                    list (APPEND __copy_commands COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${__crate_binary_files_dylib_implib}" "${__crate_binary_files_dylib_implib_copy}")
                endif ()

                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Add shared library:\"${__crate_target_namespace}::${__crate_name}_${__type}\"")
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Library:${__crate_binary_files_dylib_copy}")
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Implib:${__crate_binary_files_dylib_implib_copy}")
                add_library ("${__crate_target_namespace}::${__crate_name}_${__type}" SHARED IMPORTED GLOBAL)
                set_target_properties ("${__crate_target_namespace}::${__crate_name}_${__type}"
                    PROPERTIES
                        IMPORTED_LOCATION "${__crate_binary_files_dylib_copy}"
                        IMPORTED_IMPLIB "${__crate_binary_files_dylib_implib_copy}"
                        INTERFACE_LINK_LIBRARIES "${__crate_linkable_depends}"
                )
            endif ()
        elseif ("${__type}" MATCHES [=[^staticlib$]=])
            set (__crate_has_static TRUE)
            set (__crate_binary_files_staticlib "${__crate_binary_dir}/${__RUST_STATICLIB_PREFIX}${__crate_name}${__RUST_STATICLIB_SUFFIX}")
            set (__crate_binary_files_staticlib_copy "${CMAKE_CURRENT_BINARY_DIR}/${__RUST_STATICLIB_PREFIX}${__crate_name}${__RUST_STATICLIB_SUFFIX}")
            list (APPEND __crate_binary_files "${__crate_binary_files_staticlib_copy}")
            list (APPEND __copy_commands COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${__crate_binary_files_staticlib}" "${__crate_binary_files_staticlib_copy}")

            if (${__crate_is_imported_target})
                set (__crate_is_staticlib_linkable TRUE)
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Add static library:\"${__crate_target_namespace}::${__crate_name}_${__type}\"")
                __RUST_STATUS_MESSAGE (${__crate_is_quiet} "Library:${__crate_binary_files_staticlib_copy}")
                add_library ("${__crate_target_namespace}::${__crate_name}_${__type}" IMPORTED GLOBAL)
                set_target_properties ("${__crate_target_namespace}::${__crate_name}_${__type}"
                    PROPERTIES
                        IMPORTED_LOCATION "${__crate_binary_files_staticlib_copy}"
                        INTERFACE_LINK_LIBRARIES "${__crate_linkable_depends}"
                )
            endif ()
        elseif ("${__type}" MATCHES [=[^rlib$]=])
            set (__crate_has_rlib TRUE)
            set (__crate_binary_files_rlib "${__crate_binary_dir}/${__RUST_RLIB_PREFIX}${__crate_name}${__RUST_RLIB_SUFFIX}")
            set (__crate_binary_files_rlib_copy "${CMAKE_CURRENT_BINARY_DIR}/${__RUST_RLIB_PREFIX}${__crate_name}${__RUST_RLIB_SUFFIX}")
            list (APPEND __crate_binary_files "${__crate_binary_files_rlib_copy}")
            list (APPEND __copy_commands COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${__crate_binary_files_rlib}" "${__crate_binary_files_rlib_copy}")
        endif ()
    endforeach ()

    list (LENGTH __crate_binary_files __length)

    if (${__length} GREATER_EQUAL 1)
        add_custom_target (
            "CargoBuild_${__crate_name}"
            COMMAND "${RUST_CARGO_EXECUTABLE}" "${__crate_build_command}" ${__crate_build_options}
            ${__copy_commands}
            COMMAND_EXPAND_LISTS
            ${__job_pool_options}
            DEPENDS ${__crate_linkable_depends} ${__crate_rust_depend} ${__crate_binary_files}
            WORKING_DIRECTORY "${__crate_source_dir}"
            COMMENT "Build crate '${__crate_name}...(target_dir:${__crate_target_dir})'"
        )
        add_custom_command (
            OUTPUT ${__crate_binary_files}
            COMMAND "${RUST_CARGO_EXECUTABLE}" "${__crate_build_command}" ${__crate_build_options}
            ${__copy_commands}
            COMMAND_EXPAND_LISTS
            ${__job_pool_options}
            DEPENDS ${__crate_linkable_depends} ${__crate_rust_depend}
            WORKING_DIRECTORY "${__crate_source_dir}"
            COMMENT "Build crate '${__crate_name}...(target_dir:${__crate_target_dir})'"
        )
    else ()
        add_custom_target (
            "CargoBuild_${__crate_name}"
            COMMAND "${RUST_CARGO_EXECUTABLE}" "${__crate_build_command}" "${RUST_CARGO_EXECUTABLE}" ${__crate_build_options}
            ${__copy_commands}
            COMMAND_EXPAND_LISTS
            ${__job_pool_options}
            DEPENDS ${__crate_linkable_depends} ${__crate_rust_depend}
            WORKING_DIRECTORY "${__crate_source_dir}"
            COMMENT "Build crate '${__crate_name}...(target_dir:${__crate_target_dir})'"
        )
    endif ()

    __RUST_HANDLE_AND_EXPORT ("${__crate_name}" "${__crate_binary_dir}"
        DEPENDS ${__crate_depends}
    )
    set_property (
        TARGET "CargoBuild_${__crate_name}"
        PROPERTY
            FOLDER "CargoOptions"
    )

    if (
        DEFINED __crate_binary_files_exe AND
        ${__crate_is_imported_target} AND
        NOT("${__crate_target_alias_name}" STREQUAL "")
    )
        __RUST_STATUS_MESSAGE (${__crate_is_quiet} "${__crate_target_namespace}::${__crate_name} -> ${__crate_target_alias_name}")
        add_executable ("${__crate_target_alias_name}" ALIAS "${__crate_target_namespace}::${__crate_name}")
    endif ()

    if (
        (DEFINED __crate_binary_files_dylib OR DEFINED __crate_binary_files_staticlib) AND
        ${__crate_is_imported_target} AND
        NOT("${__crate_target_alias_name}" STREQUAL "")
    )
        __RUST_STATUS_MESSAGE (${__crate_is_quiet} "${__crate_target_namespace}::${__crate_name}_${__crate_default_type} -> ${__crate_target_namespace}::${__crate_name}")
        add_library ("${__crate_target_namespace}::${__crate_name}" ALIAS "${__crate_target_namespace}::${__crate_name}_${__crate_default_type}")

        if (NOT("${__crate_target_alias_name}" STREQUAL ""))
            __RUST_STATUS_MESSAGE (${__crate_is_quiet} "${__crate_target_namespace}::${__crate_name}_${__crate_default_type} -> ${__crate_target_alias_name}")
            add_library ("${__crate_target_alias_name}" ALIAS "${__crate_target_namespace}::${__crate_name}_${__crate_default_type}")
        endif ()
    endif ()

    set ("${__crate_name}_RUST_TAG" "" CACHE STRING "Tag")
    set ("${__crate_name}_BINARY_FILE" "${__crate_binary_files}" CACHE FILEPATH "Generated file" FORCE)
    set ("${__crate_name}_TARGET_NAMESPACE" "${__crate_target_namespace}" CACHE STRING "Imported target namespace." FORCE)
    set ("${__crate_name}_CRATE_TYPE" "${__crate_crate_type}" CACHE STRING "crate-type" FORCE)
    set ("${__crate_name}_BINARY_DIR" "${__crate_binary_dir}" CACHE FILEPATH "binary dir" FORCE)
    set ("${__crate_name}_DEFAULT_CRATE_TYPE" "${__crate_default_type}" CACHE STRING "" FORCE)
    set ("${__crate_name}_DEPENDS" "${__crate_depends}" CACHE STRING "" FORCE)
endfunction ()

find_package_handle_standard_args (
    Rust
    REQUIRED_VARS
        RUST_RUSTC_EXECUTABLE
        RUST_RUSTDOC_EXECUTABLE
        RUST_CARGO_EXECUTABLE
        RUST_RUSTUP_EXECUTABLE
    VERSION_VAR
        RUST_VERSION
)

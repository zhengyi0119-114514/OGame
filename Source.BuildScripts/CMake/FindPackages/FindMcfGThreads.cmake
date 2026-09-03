#[=======================================================================[.rst:
FindMcfGThreads
--------------
Download and find McfGThreads.

Imported Targets
^^^^^^^^^^^^^^^^
The module provides the following imported targets,if found:
``McfGThreads::McfGThreads``
    The McfGThreads library.
``McfGThreads::Minimal``
    The McfGThreads minimal library.

Result Variables
^^^^^^^^^^^^^^^^
The module defines the following variables,if found:

``McfGThreads_FOUND``
    Boolean indicating whether (the requested version of) McfGThreads was found.
``McfGThreads_INCLUDE_DIRS``
    Include directories needed to use McfGThreads.
``McfGThreads_LOCATION``
    Libraries need to copy to output directory to use McfGThreads.
``McfGThreads_LIBRARIES``
    Libraries need to link to use McfGThreads.
``McfGThreads_MINIMAL_LIBRARIES``
    Libraries need to copy to output directory to use McfGThreads::Minimal.
``McfGThreads_MINIMAL_LOCATION``
    Libraries need to link to use McfGThreads::Minimal.


Hints
^^^^^
The module the following variables before calling ``find_package(McfGThreads)``
to influence this module's behavior:

``McfGThreads_DOWNLOAD_FROM_NETWORK``
 TODO:

``McfGThreads_DOWNLOAD_VERSION``
 TODO:

``McfGThreads_DOWNLOAD_SOURCE``
 TODO:

``McfGThreads_DOWNLOAD_MSYS2_REPO``
 TODO:

``McfGThreads_ROOT_DIR``
 TODO:

Distributed under the MIT License
]=======================================================================]
cmake_minimum_required(VERSION 3.20)
include(FindPackageHandleStandardArgs)
find_package(PkgConfig QUIET)

set(__mcfgthreads_binary_root "")

set(__mcfgthreads_source msys2)
set(__mcfgthreads_binary_directories)
set(__mcfgthreads_source_regex [=[^(msys2|ustc|bfsu|github)$]=])
set(__mcfgthreads_processor)
set(__mcfgthreads_version)
set(__mcfgthreads_binary_url)
set(__mcfgthreads_msys2_repo)
set(__mcfgthreads_binary_file)
set(__mcfgthreads_binary_url_msys https://repo.msys2.org)
set(__mcfgthreads_binary_url_bfsu https://mirrors.bfsu.edu.cn/msys2)
set(__mcfgthreads_binary_url_ustc https://mirrors.ustc.edu.cn/msys2)

function(__mcfgthreads_status_message)
    if(NOT McfGThreads_FIND_QUIET)
        message(STATUS ${ARGN})
    endif()
endfunction()

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    return()
endif()
# 从网络下载
if(McfGThreads_DOWNLOAD_FROM_NETWORK)
    # 选择下载版本
    if(McfGThreads_DOWNLOAD_VERSION)
        set(__mcfgthreads_version "${McfGThreads_DOWNLOAD_VERSION}")
    elseif(DEFINED McfGThreads_FIND_VERSION AND (McfGThreads_FIND_VERSION MATCHES [=[^([0-9]+)\.([0-9]+)\.([0-9]+)$]=]))
        set(__mcfgthreads_version "${McfGThreads_FIND_VERSION}")
    else()
        set(__mcfgthreads_version 2.4.2)
    endif()
    set(__mcfgthreads_file "${CMAKE_BINARY_DIR}/extern/download/mcfgthread-${__mcfgthreads_version}.tar.zst")
    set(__mcfgthreads_binary_file "${CMAKE_BINARY_DIR}/extern/download/mcfgthread-lib-${__mcfgthreads_version}.tar.zst")
    set(__mcfgthreads_extract_directory "${CMAKE_BINARY_DIR}/extern/mcfgthread-${__mcfgthreads_version}")
    if(McfGThreads_DOWNLOAD_SOURCE AND (McfGThreads_DOWNLOAD_SOURCE MATCHES [=[^(github)$]=]))
        # 如果从Github下载，则只支持下载"vXXX.XXX General Availability XXX Release"版本，其中三个将依次填入主版本号，次版本号
        # 补丁(PATCH)版本号。
        if((CMAKE_SYSTEM_PROCESSOR MATCHES [=[^(AMD64|[Xx]64|x86_64)$]=])
           OR (CMAKE_GENERATOR_PLATFORM MATCHES [=[^(x64)$]=])
           OR (CMAKE_VS_PLATFORM_NAME MATCHES [=[^(x64)$]=]))
            set(__mcfgthreads_process_arch "x86_64")
            set(__mcfgthreads_msys2_repo "mingw64")
        elseif(
            CMAKE_SYSTEM_PROCESSOR MATCHES [=[^(X86|i386|i486|i686)$]=]
            OR (CMAKE_GENERATOR_PLATFORM MATCHES [=[^(Win32)$]=])
            OR (CMAKE_VS_PLATFORM_NAME MATCHES [=[^(Win32)$]=]))
            set(__mcfgthreads_process_arch "i686")
            set(__mcfgthreads_msys2_repo "mingw32")
        else()
            message(WARNING "Unsupport processor ${CMAKE_SYSTEM_PROCESSOR}")
        endif()
        if(NOT
           ((EXISTS "${__mcfgthreads_file}")
            AND (EXISTS "${__mcfgthreads_binary_file}")
            AND (EXISTS "${__mcfgthreads_extract_directory}")))

            string(REGEX REPLACE [=[^([0-9]+)\.([0-9]+)(\.[0-9]+)?$]=] [=[\1.\2]=] __mcfgthreads_major_version_and_minor_version "${__mcfgthreads_version}")
            string(REGEX REPLACE [=[^[0-9]+\.[0-9]+(\.([0-9]+))?$]=] [=[\2]=] __mcfgthreads_patch_version "${__mcfgthreads_version}")
            string(APPEND __mcfgthreads_lib_url "https://github.com/lhmouse/mcfgthread/releases/download/" "v${__mcfgthreads_major_version_and_minor_version}-ga.${__mcfgthreads_patch_version}/"
                   "mingw-w64-${__mcfgthreads_process_arch}-mcfgthread-libs-${__mcfgthreads_version}-1-any.pkg.tar.zst")
            string(APPEND __mcfgthreads_url "https://github.com/lhmouse/mcfgthread/releases/download/" "v${__mcfgthreads_major_version_and_minor_version}-ga.${__mcfgthreads_patch_version}/"
                   "mingw-w64-${__mcfgthreads_process_arch}-mcfgthread-${__mcfgthreads_version}-1-any.pkg.tar.zst")
            # message(STATUS "${__mcfgthreads_lib_url}" \n "${__mcfgthreads_url}")

            file(DOWNLOAD "${__mcfgthreads_lib_url}" "${__mcfgthreads_binary_file}")
            file(DOWNLOAD "${__mcfgthreads_url}" "${__mcfgthreads_file}")
            file(ARCHIVE_EXTRACT INPUT "${__mcfgthreads_file}" DESTINATION "${__mcfgthreads_extract_directory}")
            file(ARCHIVE_EXTRACT INPUT "${__mcfgthreads_binary_file}" DESTINATION "${__mcfgthreads_extract_directory}")
        endif()
        # example https://github.com/lhmouse/mcfgthread/releases/download/v2.4-ga.2/mingw-w64-x86_64-mcfgthread-libs-2.4.2-1-any.pkg.tar.zst
        set(__mcfgthreads_binary_root "${__mcfgthreads_extract_directory}/${__mcfgthreads_msys2_repo}")
    elseif(McfGThreads_DOWNLOAD_SOURCE AND (McfGThreads_DOWNLOAD_SOURCE MATCHES [=[^(msys2|ustc|bfsu)$]=]))
        if(McfGThreads_DOWNLOAD_MSYS2_REPO AND (McfGThreads_DOWNLOAD_MSYS2_REPO MATCHES [=[^(mingw64|ucrt64|clang64|clangarm64)$]=]))
            set(__mcfgthreads_msys2_repo "${McfGThreads_DOWNLOAD_MSYS2_REPO}")
        else()
            if(CMAKE_GENERATOR_PLATFORM)
                if(CMAKE_GENERATOR_PLATFORM STREQUAL [=[x64]=])
                    set(__mcfgthreads_msys2_repo "mingw64")
                elseif(CMAKE_GENERATOR_PLATFORM STREQUAL [=[ARM64]=])
                    set(__mcfgthreads_msys2_repo "clangarm64")
                endif()
            elseif(CMAKE_SYSTEM_PROCESSOR)
                if(CMAKE_SYSTEM_PROCESSOR MATCHES [=[^(AMD64|x64|x86_64)$]=])
                    set(__mcfgthreads_msys2_repo "mingw64")
                elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL [=[^(ARM64|aarch64)$]=])
                    set(__mcfgthreads_msys2_repo "clangarm64")
                endif()
            endif()
            set(__mcfgthreads_msys2_repo "mingw64")
        endif()
        if(__mcfgthreads_msys2_repo MATCHES [=[^(mingw64)$]=])
            set(__mcfgthreads_url_file_prefix "mingw-w64-x86_64")
        elseif(__mcfgthreads_msys2_repo MATCHES [=[^(ucrt64)$]=])
            set(__mcfgthreads_url_file_prefix "mingw-w64-ucrt-x86_64")
        elseif(__mcfgthreads_msys2_repo MATCHES [=[^(clang64)$]=])
            set(__mcfgthreads_url_file_prefix "mingw-w64-clang-x86_64")
        elseif(__mcfgthreads_msys2_repo MATCHES [=[^(clangarm64)$]=])
            set(__mcfgthreads_url_file_prefix "mingw-w64-clang-aarch64")
        endif()
        if(NOT ((EXISTS "${__mcfgthreads_binary_file}") AND (EXISTS "${__mcfgthreads_extract_directory}")))
            if(McfGThreads_DOWNLOAD_SOURCE MATCHES [=[^msys2$]=])
                set(__mcfgthreads_mirror_url "${__mcfgthreads_binary_url_msys}")
            elseif(McfGThreads_DOWNLOAD_SOURCE MATCHES [=[^(ustc)$]=])
                set(__mcfgthreads_mirror_url "${__mcfgthreads_binary_url_ustc}")
            elseif(McfGThreads_DOWNLOAD_SOURCE MATCHES [=[^(bfsu)$]=])
                set(__mcfgthreads_mirror_url "${__mcfgthreads_binary_url_bfsu}")
            endif()
            set(__mcfgthreads_url "${__mcfgthreads_mirror_url}/mingw/${__mcfgthreads_msys2_repo}/${__mcfgthreads_url_file_prefix}-mcfgthread-${__mcfgthreads_version}-1-any.pkg.tar.zst")
            set(__mcfgthreads_binary_url "${__mcfgthreads_mirror_url}/mingw/${__mcfgthreads_msys2_repo}/${__mcfgthreads_url_file_prefix}-mcfgthread-libs-${__mcfgthreads_version}-1-any.pkg.tar.zst")
            file(DOWNLOAD "${__mcfgthreads_binary_url}" "${__mcfgthreads_binary_file}")
            file(DOWNLOAD "${__mcfgthreads_url}" "${__mcfgthreads_file}")
            file(ARCHIVE_EXTRACT INPUT "${__mcfgthreads_file}" DESTINATION "${__mcfgthreads_extract_directory}")
            file(ARCHIVE_EXTRACT INPUT "${__mcfgthreads_binary_file}" DESTINATION "${__mcfgthreads_extract_directory}")
        endif()
        set(__mcfgthreads_binary_root "${__mcfgthreads_extract_directory}/${__mcfgthreads_msys2_repo}")
    endif()
    if(DEFINED __mcfgthreads_binary_root AND EXISTS "${__mcfgthreads_binary_root}")
        list(APPEND __mcfgthreads_binary_directories "${__mcfgthreads_binary_root}")
    endif()
endif()

if(DEFINED McfGThreads_ROOT_DIR AND EXISTS "${McfGThreads_ROOT}")
    list(APPEND __mcfgthreads_binary_directories "${McfGThreads_ROOT_DIR}")
endif()
if(DEFINED CMAKE_FIND_ROOT_PATH AND EXISTS "${CMAKE_FIND_ROOT_PATH}")
    list(APPEND __mcfgthreads_binary_directories "${CMAKE_FIND_ROOT_PATH}")
endif()
if(DEFINED CMAKE_SYSROOT AND EXISTS "${CMAKE_SYSROOT}")
    list(APPEND __mcfgthreads_binary_directories "${CMAKE_SYSROOT}")
endif()

foreach(__root_directory IN LISTS __mcfgthreads_binary_directories)
    set(__library_directory "${__root_directory}/lib")
    set(__include_directory "${__root_directory}/include")
    set(__pkgconfig_directory "${__root_directory}/lib/pkgconfig")
    set(__runtime_directory "${__root_directory}/bin")
    find_library(
        __library
        NAMES libmcfgthread mcfgthread libmcfgthread.dll mcfgthread.dll
        PATHS "${__library_directory}")
    find_library(
        __minimal_library
        NAMES libmcfgthread-minimal mcfgthread-minimal libmcfgthread-minimal.dll mcfgthread-minimal.dll
        PATHS "${__library_directory}")
    find_file(
        __library_runtime
        NAMES libmcfgthread-2.dll libmcfgthread.dll mcfgthread-2.dll mcfgthread.dll
        PATHS "${__runtime_directory}"
        NO_DEFAULT_PATH)
    find_file(
        __minimal_library_runtime
        NAMES libmcfgthread-minimal-2.dll mcfgthread-minimal-2.dll libmcfgthread-minimal.dll mcfgthread-minimal.dll
        PATHS "${__runtime_directory}")
    find_file(
        __pkgconfig
        NAMES mcfgthread.pc
        PATHS "${__pkgconfig_directory}")
    # message(STATUS "${__library}" "\n" "${__minimal_library}" \n "${__runtime_directory}" "\n" "${__library_runtime}" "\n" "${__minimal_library_runtime}")
    if((EXISTS "${__include_directory}")
       AND __library
       AND __minimal_library
       AND __pkgconfig
       AND __library_runtime
       AND __minimal_library_runtime)
        set(McfGThreads_FOUND TRUE)
        set(McfGThreads_INCLUDE_DIRS "${__include_directory}")
        set(McfGThreads_PkgConfig_DIRECTORY "${__pkgconfig_directory}")
        set(McfGThreads_LIBRARIES "${__library}")
        set(McfGThreads_LOCATION "${__library_runtime}")
        set(McfGThreads_MINIMAL_LIBRARIES "${__minimal_library}")
        set(McfGThreads_MINIMAL_LOCATION "${__minimal_library_runtime}")
        set(ENV{PKG_CONFIG_PATH} "${McfGThreads_PkgConfig_DIRECTORY};$ENV{PKG_CONFIG_PATH}")
        pkg_check_modules(PkgConfigMcfGThreads REQUIRED QUIET mcfgthread)
        break()
    endif()
endforeach()
if(NOT McfGThreads_FOUND AND PkgConfig_FOUND)
    pkg_check_modules(PkgConfigMcfGThreads mcfgthread)
    if(PkgConfigMcfGThreads_FOUND)
        set(McfGThreads_INCLUDE_DIRS "${PkgConfigMcfGThreads_INCLUDE_DIRS}")
        set(McfGThreads_LOCATION "${PkgConfigMcfGThreads_LIBRARIES}")
        set(McfGThreads_LIBRARIES "${PkgConfigMcfGThreads_LIBRARIES}")
        set(McfGThreads_MINIMAL_LIBRARIES)
        set(McfGThreads_MINIMAL_LOCATION)
        set(McfGThreads_FOUND TRUE)
    endif()
endif()

unset(__library_directory)
unset(__library)
unset(__library_runtime)
unset(__include_directory)
unset(__pkgconfig_directory)
unset(__minimal_library)
unset(__minimal_library_runtime)
unset(__pkgconfig)

if(__mcfgthreads_version)
    set(McfGThreads_VERSION "${__mcfgthreads_version}")
elseif(PkgConfigMcfGThreads_VERSION VERSION_GREATER 0)
    set(McfGThreads_VERSION "${PkgConfigMcfGThreads_VERSION}")
endif()

if(McfGThreads_LIBRARIES
   AND McfGThreads_INCLUDE_DIRS
   AND McfGThreads_LOCATION
   AND McfGThreads_PkgConfig_DIRECTORY)
    message("${McfGThreads_MINIMAL_LIBRARIES}:${McfGThreads_MINIMAL_LOCATION}")
    set(McfGThreads_FOUND TRUE)
    add_library(McfGThreads::McfGThreads SHARED IMPORTED GLOBAL)
    set_target_properties(
        McfGThreads::McfGThreads
        PROPERTIES
            IMPORTED_IMPLIB "${McfGThreads_LIBRARIES}"
            IMPORTED_LOCATION "${McfGThreads_LOCATION}"
            INTERFACE_LINK_LIBRARIES "ntdll"
            INTERFACE_INCLUDE_DIRECTORIES "${McfGThreads_INCLUDE_DIRS}")
    if(McfGThreads_MINIMAL_LIBRARIES AND McfGThreads_MINIMAL_LOCATION)
        add_library(McfGThreads::Minimal SHARED IMPORTED GLOBAL)
        set_target_properties(
            McfGThreads::Minimal
            PROPERTIES
                IMPORTED_IMPLIB "${McfGThreads_MINIMAL_LIBRARIES}"
                IMPORTED_LOCATION "${McfGThreads_MINIMAL_LOCATION}"
                INTERFACE_LINK_LIBRARIES "ntdll"
                INTERFACE_INCLUDE_DIRECTORIES "${McfGThreads_INCLUDE_DIRS}")
    endif()
endif()

find_package_handle_standard_args(
    McfGThreads
    REQUIRED_VARS
        McfGThreads_FOUND
        McfGThreads_LIBRARIES
        McfGThreads_INCLUDE_DIRS
        # McfGThreads_LOCATION
        # McfGThreads_MINIMAL_LIBRARIES
        # McfGThreads_MINIMAL_LOCATION
        # McfGThreads_PkgConfig_DIRECTORY
    VERSION_VAR McfGThreads_VERSION
    HANDLE_COMPONENTS
    FAIL_MESSAGE "Failed to find mcfgthreads.")

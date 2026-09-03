cmake_minimum_required(VERSION 3.28)
include(CMakeDependentOption)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "请务必别在源代码构建捏，亲。")
endif()

project(open_stg VERSION 0.1.0)
option("EnableLibdwarf" "Use libdwarf to get debug information." TRUE)
option("EnableUnicode" "Use libdwarf to get debug information." TRUE)

find_package(PkgConfig QUIET)
if(EnableLibdwarf)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.1)
        cmake_pkg_config(IMPORT libdwarf REQUIRED PREFIX Libdwarf)
    elseif(PkgConfig_FOUND)
        pkg_check_modules(Libdwarf QUIET IMPORTED_TARGET "libdwarf")
    else()
        message(FATAL_ERROR "Libdwarf not found.")
    endif()
endif()
if(EnableUnicode)
    if(WIN32)
        find_package(ICU REQUIRED COMPONENTS dt in io uc)
    else()
        find_package(ICU REQUIRED COMPONENTS data i18n io uc)
    endif()
endif()
if(LoaderArchitecture AND NOT (LoaderArchitecture STREQUAL "Auto"))
    if(NOT (LoaderArchitecture MATCHES [=[^(MicrokernelLike|OneProcess)$]=]))
        message(FATAL_ERROR "Invaild value '${LoaderArchitecture}' for 'LoaderArchitecture'.")
    endif()
else()
    if(CMAKE_SYSTEM_NAME MATCHES [=[^(CYGWIN|MSYS|Windows|WindowsPhone)$]=])
        set(LoaderArchitecture OneProcess)
    else()
        set(LoaderArchitecture MicrokernelLike)
    endif()
endif()
if(ThreadsLibrary AND NOT (ThreadsLibrary STREQUAL "Auto"))
    if(NOT (ThreadsLibrary MATCHES [=[^(C11Threads|Pthread|McfGThread)$]=]))
        message(FATAL_ERROR "Invaild value '${ThreadsLibrary}' for 'ThreadsLibrary'")
    endif()
    if(ThreadsLibrary STREQUAL "McfGThread")
        if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.1)
            cmake_pkg_config(IMPORT mcfgthread REQUIRED PREFIX "McfGThread")
        elseif(PkgConfig_FOUND)
            pkg_check_modules(McfGThread REQUIRED QUIET IMPORTED_TARGET "mcfgthread")
        endif()
    elseif(ThreadsLibrary STREQUAL "Pthread")
        find_package(Threads REQUIRED)
    elseif(ThreadsLibrary STREQUAL "C11Threads")
    else()
        message(FATAL_ERROR "Invaild value '${ThreadsLibrary}' for 'ThreadsLibrary'.")
    endif()
else()
    find_package(Threads)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 4.1)
        cmake_pkg_config(IMPORT mcfgthread QUIET PREFIX "McfGThread")
    elseif(PkgConfig_FOUND)
        pkg_check_modules(McfGThread QUIET IMPORTED_TARGET "mcfgthread")
    endif()
    if(McfGThread_FOUND)
        set(ThreadsLibrary McfGThread)
    elseif(Threads_FOUND)
        set(ThreadsLibrary Pthread)
    else()
        set(ThreadsLibrary C11Threads)
    endif()
endif()

add_library(OpenStgBase SHARED)
target_sources(OpenStgBase
    PRIVATE
    Source.CAndCpp/OpenStgBase/StringCopy.c
    Source.CAndCpp/OpenStgBase/StringLength.c
)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.23)
    target_sources(OpenStgBase
        PUBLIC
        FILE_SET HEADERS
        FILES
        Source.CAndCpp/Include/OpenStg/Base/Base.h
        Source.CAndCpp/Include/OpenStg/Base/String.h
    )
endif()
target_include_directories(OpenStgBase
    PRIVATE
    Source.CAndCpp/Include
)
target_compile_definitions(
    OpenStgBase
    PUBLIC
    "OgMacroOptionsEnableLibdwarfComponent=$<BOOL:${EnableLibdwarf}>"
    "OgMacroOptionsEnableUnicode=$<BOOL:${EnableUnicode}>"
    "OgMacroOptionsLoaderArchitecture=\"${LoaderArchitecture}\""
    "OgMacroOptionsThreadsLibrary=\"${ThreadsLibrary}\""
)
set_target_properties(OpenStgBase
    PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED TRUE
    C_EXTENSIONS TRUE
)
target_link_libraries(OpenStgBase
    PUBLIC
    $<TARGET_NAME_IF_EXISTS:PkgConfig::Libdwarf>
    $<$<STREQUAL:${ThreadsLibrary},McfGThread>:PkgConfig::McfGThread>
    $<$<STREQUAL:${ThreadsLibrary},Pthread>:Threads::Threads>
)
# 定义资源文件路径
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Rsesources")

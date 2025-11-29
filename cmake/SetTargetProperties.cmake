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

if(
    "${CMAKE_SYSTEM_NAME}" STREQUAL "Windows" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsPhone" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "WindowsStore" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "MSYS" OR
    "${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN"
)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        # - Fixes msvc toolchain issue
        # cmake dosen't set `CMAKE_HOST_SYSTEM_PROCESSOR` before `project(...)`, which led to the failure of msvc configuration
        if(DEFINED ENV{PROCESSOR_ARCHITEW6432})
            set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITEW6432}")
        elseif(DEFINED ENV{PROCESSOR_ARCHITECTURE})
            set(CMAKE_HOST_SYSTEM_PROCESSOR "$ENV{PROCESSOR_ARCHITECTURE}")
        endif()

        target_compile_options(
            open_stg_lib
            PUBLIC
            /utf-8
        )
        target_compile_definitions(
            open_stg_lib
            PUBLIC
            _CRT_SECURE_NO_WARNINGS
        )
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        target_compile_options(open_stg_lib
            PUBLIC "-fexec-charset=UTF-8"
        )
    endif()

    target_compile_definitions(
        open_stg_lib
        PUBLIC
        WINDOWS32
    )
elseif(UNIX)
    target_compile_definitions(
        open_stg_lib
        PRIVATE
        POSIX=true
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(
        open_stg_lib
        PUBLIC
        LINUX=true
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(
        open_stg_lib
        PRIVATE
        _DEBUG
        DEBUG
    )
endif()

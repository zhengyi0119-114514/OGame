find_program(__LLD_FOUND NAMES "lld")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "ARMClang"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IntelLLVM"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "CrayClang"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "IBMClang"
   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "TIClang")
    set(__IS_CLANG TRUE)
else()
    set(__IS_CLANG FALSE)
endif()

if(${__IS_CLANG} AND NOT "${__LLD_FOUND}" STREQUAL "__LLD_FOUND-NOTFOUND")
    if(${CMAKE_VERSION} VERSION_GREATER_EQUAL 3.29)
        set(CMAKE_LINKER_TYPE LLD)
    else()
        add_link_options("-fuse-ld=lld")
    endif()
endif()

if(${__IS_CLANG})
    set(CMAKE_C_CLANG_TIDY clang-tidy)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

cmake_host_system_information(RESULT __parallel QUERY NUMBER_OF_LOGICAL_CORES)
set(CMAKE_BUILD_PARALLEL_LEVEL ${__parallel})
message(STATUS "parallel:${__parallel}")

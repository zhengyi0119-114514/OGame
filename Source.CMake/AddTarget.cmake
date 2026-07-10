# LICENSE: MIT
if(NOT DEFINED __ADD_TARGET_TAG)
    set(__ADD_TARGET_TAG)
    set(__empty_c_source "${CMAKE_CURRENT_BINARY_DIR}/empty.c")
    include(CheckCompilerFlag)
    include(CheckCCompilerFlag)
    include(CheckCXXCompilerFlag)
    include(CheckFortranCompilerFlag)
    include(CheckLinkerFlag)

    if(EXISTS "${__ADD_TARGET_COPY_IF_EXIST_SCRIPT}")
        set(__ADD_TARGET_COPY_IF_EXIST_SCRIPT_EXIST TRUE)
    else()
        set(__ADD_TARGET_COPY_IF_EXIST_SCRIPT_EXIST FALSE)
    endif()

    function(add_target __target)
        set(__OPTIONS "WIN32" "MACOSX_BUNDLE" "EXCLUDE_FROM_ALL" "LLVM" "BOTH_SHARED_AND_STATIC")
        set(__MULTI_VALUE_KEYWORDS
            "LINK_DEPENDS" #
            "SOURCES" #
            "HEADERS" #
            "INCLUDE_DIRS" #
            "MODULES" #
            "LINK_OPTIONS" #
            "COMPILE_OPTIONS" #
            "COMPILE_DEFINITIONS" #
            "COMPILE_FEATURES"
            "TARGET_PROPERTIES" #
        )
        cmake_parse_arguments(
            PARSE_ARGV 1 "__TARGET" "${__OPTIONS}" # Options
            "TARGET_TYPE" # OneValueKeywords
            "${__MULTI_VALUE_KEYWORDS}" # MultiValueKeywords
        )
        set(__target_type "${__TARGET_TARGET_TYPE}")
        set(__target_depends "${__TARGET_DEPENDS}")
        set(__target_link_depends "${__TARGET_LINK_DEPENDS}")
        set(__target_sources "${__TARGET_SOURCES}")
        set(__target_headers "${__TARGET_HEADERS}")
        set(__target_include_dir "${__TARGET_INCLUDE_DIRS}")
        set(__target_modules "${__TARGET_MODULES}")
        set(__target_properties "${__TARGET_TARGET_PROPERTIES}")
        set(__target_compile_options "${__TARGET_COMPILE_OPTIONS}")
        set(__target_compile_definitions "${__TARGET_COMPILE_DEFINITIONS}")
        set(__target_link_options "${__TARGET_LINK_OPTIONS}")
        set(__target_compile_features "${__TARGET_COMPILE_FEATURES}")

        if("${__TARGET_LLVM}")
            find_package(LLVM REQUIRED CONFIG)
            include(AddLLVM)
        endif()

        if(NOT "${__target_type}" MATCHES "^((EXE(CUTABLE)?)|(SHARED(_LIBRARY)?)|(STATIC(_LIBRARY)?)|(OBJECT(_LIBRARY)?)|(INTERFACE(_LIBRARY)?))$")
            message(FATAL_ERROR "Unknown target type:${__TARGET_TARGET_TYPE}")
        endif()

        if(NOT EXISTS "${__empty_c_source}")
            execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "touch" "${__empty_c_source}" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
            file(APPEND "${__empty_c_source}" [=[//真的没有东西！！你还看来干嘛？]=])
        endif()

        if("${__target_type}" MATCHES "^EXE(CUTABLE)?$")
            set(__target_options)

            if("${__TARGET_WIN32}")
                list(APPEND __target_options "WIN32")
            endif()

            if("${__TARGET_MACOSX_BUNDLE}")
                list(APPEND __target_options "MACOSX_BUNDLE")
            endif()

            if("${__TARGET_EXCLUDE_FROM_ALL}")
                list(APPEND __target_options "EXCLUDE_FROM_ALL")
            endif()

            if("${__TARGET_LLVM}")
                add_llvm_executable("${__target}" "${__target_options}" "${__empty_c_source}")
                message(STATUS "Add Target(EXECUTABLE)(LLVM):${__target}")
            else()
                add_executable("${__target}" ${__target_options} "${__empty_c_source}")
                message(STATUS "Add Target(EXECUTABLE):${__target}")
            endif()
        elseif("${__target_type}" MATCHES "^SHARED(_LIBRARY)?$")
            set(__target_options)

            if("${__TARGET_EXCLUDE_FROM_ALL}")
                list(APPEND __target_options "EXCLUDE_FROM_ALL")
            endif()

            # add_library("${__target}" SHARED "${__empty_c_source}")
            if("${__TARGET_LLVM}")
                add_llvm_library("${__target}" SHARED "${__empty_c_source}")
                message(STATUS "Add Target(SHARED LIBRARY)(LLVM):${__target}")
            else()
                add_library("${__target}" SHARED "${__empty_c_source}")
                message(STATUS "Add Target(SHARED LIBRARY):${__target}")
            endif()
        elseif("${__target_type}" MATCHES "^STATIC(_LIBRARY)?$")
            set(__target_options)

            if("${__TARGET_EXCLUDE_FROM_ALL}")
                list(APPEND __target_options "EXCLUDE_FROM_ALL")
            endif()

            if("${__TARGET_LLVM}")
                message(FATEL_ERROR "LLVM target donot support static library.")
            else()
                add_library("${__target}" STATIC "${__empty_c_source}")
                message(STATUS "Add Target(STATIC LIBRARY):${__target}")
            endif()
        elseif("${__target_type}" MATCHES "^OBJECT(_LIBRARY)?$")
            set(__target_options)
            add_library("${__target}" OBJECT "${__empty_c_source}")
            message(STATUS "Add Target(OBJECT LIBRARY):${__target}")
        elseif("${__target_type}" MATCHES "^INTERFACE(_LIBRARY)?$")
            add_library("${__target}" INTERFACE)
            message(STATUS "Add Target(INTERFACE LIBRARY):${__target}")
        endif()

        if(NOT "${__target_sources}" STREQUAL "")
            target_sources("${__target}" ${__target_sources})
        endif()

        if(NOT "${__target_include_dir}" STREQUAL "")
            target_include_directories("${__target}" ${__target_include_dir})
        endif()

        if(NOT "${__target_link_depends}" STREQUAL "")
            target_link_libraries("${__target}" ${__target_link_depends})
        endif()

        if(NOT "${__target_headers}" STREQUAL "" AND "${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.23")
            target_sources("${__target}" PUBLIC FILE_SET HEADERS FILES ${__target_headers})
        endif()

        if(NOT "${__target_modules}" STREQUAL "" AND "${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.23")
            target_sources("${__target}" PUBLIC FILE_SET CXX_MODULES FILES ${__target_modules})
        endif()

        add_dependencies("${__target}" ${__target_depends})

        if(NOT "${__target_link_options}" STREQUAL "")
            target_link_options("${__target}" ${__target_link_options})
        endif()

        if(NOT "${__target_compile_options}" STREQUAL "")
            target_compile_options("${__target}" ${__target_compile_options})
        endif()

        if(NOT "${__target_compile_definitions}" STREQUAL "")
            target_compile_definitions("${__target}" ${__target_compile_definitions})
        endif()

        if(NOT "${__target_compile_features}" STREQUAL "")
            target_compile_features("${__target}" ${__target_compile_features})
        endif()

        if(NOT "${__target_properties}" STREQUAL "")
            set_target_properties("${__target}" PROPERTIES ${__target_properties})
        endif()

        if((DEFINED ADD_TARGET_BINARY_DIR)
           AND ("${__target_type}" MATCHES [=[((EXE(CUTABLE)?)|(SHARED(_LIBRARY)?)|(STATIC(_LIBRARY)?))]=])
           AND "${__ADD_TARGET_COPY_IF_EXIST_SCRIPT_EXIST}")
            set(COPY_IF_EXIST_SOURCE "$<TARGET_FILE:${__target}>")
            add_custom_command(
                TARGET "${__target}"
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}" "-D" "COPY_IF_EXIST_SOURCE=${COPY_IF_EXIST_SOURCE}" "-D" "COPY_IF_EXIST_TARGET=${ADD_TARGET_BINARY_DIR}" "-P" "${__ADD_TARGET_COPY_IF_EXIST_SCRIPT}"
                COMMENT "Copy binary file to ${ADD_TARGET_BINARY_DIR}")
        endif()
    endfunction()
    function(target_test_and_add_compile_options __target __lang)
        set(__cmake_required_quiet_backup "${CMAKE_REQUIRED_QUIET}")
        set(CMAKE_REQUIRED_QUIET FLASE)
        cmake_parse_arguments(__flag "REQUIRE" "" "PUBLIC;INTERFACE;PRIVATE" ${ARGN})
        set(__require "${__flag_REQUIRE}")
        set(__public_flags)
        set(__interface_flags)
        set(__private_flags)
        foreach(__flag IN LISTS __flag_PUBLIC)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_compiler_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __public_flags "${__flag}")
            endif()
        endforeach()
        foreach(__flag IN LISTS __flag_INTERFACE)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_compiler_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __interface_flags "${__flag}")
            endif()
        endforeach()
        foreach(__flag IN LISTS __flag_PRIVATE)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_compiler_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __private_flags "${__flag}")
            endif()
        endforeach()
        if((NOT ("${__public_flags}" STREQUAL ""))
           OR (NOT ("${__private_flags}" STREQUAL ""))
           OR (NOT ("${__interface_flags}" STREQUAL "")))
            message(STATUS "${__target}:compile options:")
            if(NOT ("${__public_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__public_flags}")
                message(STATUS "    public flags:${__output_flags}")
            endif()
            if(NOT ("${__interface_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__interface_flags}")
                message(STATUS "    interface flags:${__output_flags}")
            endif()
            if(NOT ("${__private_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__private_flags}")
                message(STATUS "    private flags:${__output_flags}")
            endif()
            target_compile_options(
                "${__target}"
                PUBLIC ${__public_flags}
                INTERFACE ${__interface_flags}
                PRIVATE ${__private_flags})
        endif()
        set(CMAKE_REQUIRED_QUIET "${__cmake_required_quiet_backup}")
    endfunction()
    function(target_test_and_add_link_options __target __lang)
        set(__cmake_required_quiet_backup "${CMAKE_REQUIRED_QUIET}")
        set(CMAKE_REQUIRED_QUIET FLASE)
        cmake_parse_arguments(__flag "" "" "PUBLIC;INTERFACE;PRIVATE" ${ARGN})
        set(__public_flags)
        set(__interface_flags)
        set(__private_flags)
        foreach(__flag IN LISTS __flag_PUBLIC)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_linker_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __public_flags "${__flag}")
            endif()
        endforeach()
        foreach(__flag IN LISTS __flag_INTERFACE)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_linker_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __interface_flags "${__flag}")
            endif()
        endforeach()
        foreach(__flag IN LISTS __flag_PRIVATE)
            set(__flag_variable_name "${__flag}")
            string(REPLACE "/" "_msvc" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE ":" "_" __flag_variable_name "${__flag_variable_name}")
            string(REPLACE "-" "_" __flag_variable_name "${__flag_variable_name}")
            check_linker_flag("${__lang}" "${__flag}" "${__flag_variable_name}")
            if("${${__flag_variable_name}}")
                list(APPEND __private_flags "${__flag}")
            endif()
        endforeach()
        if((NOT ("${__public_flags}" STREQUAL ""))
           OR (NOT ("${__private_flags}" STREQUAL ""))
           OR (NOT ("${__interface_flags}" STREQUAL "")))
            message(STATUS "${__target}:link options:")
            if(NOT ("${__public_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__public_flags}")
                message(STATUS "    public flags:${__output_flags}")
            endif()
            if(NOT ("${__interface_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__interface_flags}")
                message(STATUS "    interface flags:${__output_flags}")
            endif()
            if(NOT ("${__private_flags}" STREQUAL ""))
                string(REPLACE ";" " " __output_flags "${__private_flags}")
                message(STATUS "    private flags:${__output_flags}")
            endif()
            target_compile_options(
                "${__target}"
                PUBLIC ${__public_flags}
                INTERFACE ${__interface_flags}
                PRIVATE ${__private_flags})
        endif()
        target_link_options(
            "${__target}"
            PUBLIC
            ${__public_flags}
            INTERFACE
            ${__interface_flags}
            PRIVATE
            ${__private_flags})
        set(CMAKE_REQUIRED_QUIET "${__cmake_required_quiet_backup}")
    endfunction()
endif()

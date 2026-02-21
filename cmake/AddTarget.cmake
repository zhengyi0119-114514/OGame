# LICENSE: MIT
if(NOT DEFINED __ADD_TARGET_TAG)
    set(__ADD_TARGET_TAG)
    set(__empty_c_source "${CMAKE_CURRENT_BINARY_DIR}/empty.c")

    function(ADD_TARGET __target)
        set(__MULTI_VALUE_KEYWORDS
            "DEPENDS"
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
        cmake_parse_arguments(PARSE_ARGV 1 "__TARGET"
            "WIN32;MACOSX_BUNDLE;EXCLUDE_FROM_ALL" # Options
            "TARGET_TYPE" # OneValueKeywords
            "${__MULTI_VALUE_KEYWORDS}" # MultiValueKeywords
        )
        set(__target_type "${__TARGET_TARGET_TYPE}")
        set(__target_depends "${__TARGET_DEPENDS}")
        set(__target_link_depends "${__TARGET_LINK_DEPENDS}")
        set(__target_sources "${__TARGET_SOURCES}")
        set(__target_headers "${__TARGET_HEADERS}")
        set(__target_include_dir "${__TARGET_INCLUDE_DIR}")
        set(__target_modules "${__TARGET_MODULES}")
        set(__target_properties "${__TARGET_TARGET_PROPERTIES}")
        set(__target_compile_options "${__TARGET_COMPILE_OPTIONS}")
        set(__target_compile_definitions "${__TARGET_COMPILE_DEFINITIONS}")
        set(__target_link_options "${__TARGET_LINK_OPTIONS}")
        set(__target_compile_features "${__TARGET_COMPILE_FEATURES}")
        if(NOT "${__target_type}" MATCHES "^((EXE(CUTABLE)?)|(SHARED(_LIBRARY)?)|(STATIC(_LIBRARY)?)|(OBJECT(_LIBRARY)?)|(INTERFACE(_LIBRARY)?))$")
            message(FATAL_ERROR "Unknown target type:${__TARGET_TARGET_TYPE}")
        endif()

        if(NOT EXISTS "${__empty_c_source}")
            execute_process(
                COMMAND "${CMAKE_COMMAND}" "-E" "touch" "${__empty_c_source}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            )
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

            add_executable("${__target}" ${__target_options} "${__empty_c_source}")
        elseif("${__target_type}" MATCHES "^SHARED(_LIBRARY)?$")
            set(__target_options)

            if("${__TARGET_EXCLUDE_FROM_ALL}")
                list(APPEND __target_options "EXCLUDE_FROM_ALL")
            endif()

            add_library("${__target}" SHARED "${__empty_c_source}")
        elseif("${__target_type}" MATCHES "^STATIC(_LIBRARY)?$")
            set(__target_options)

            if("${__TARGET_EXCLUDE_FROM_ALL}")
                list(APPEND __target_options "EXCLUDE_FROM_ALL")
            endif()

            add_library("${__target}" STATIC "${__empty_c_source}")
        elseif("${__target_type}" MATCHES "^OBJECT(_LIBRARY)?$")
            set(__target_options)
            add_library("${__target}" OBJECT "${__empty_c_source}")
        elseif("${__target_type}" MATCHES "^INTERFACE(_LIBRARY)?$")
            add_library("${__target}" INTERFACE)
        endif()

        if(NOT "${__target_sources}" STREQUAL "")
            target_sources(
                "${__target}"
                ${__target_sources}
            )
        endif()

        if(NOT "${__target_include_dir}" STREQUAL "")
            target_include_directories(
                "${__target}"
                ${__target_include_dir}
            )
        endif()

        cmake_parse_arguments("__LINK_DEPEND"
            "" # Options
            "" # OneValueKeywords
            "PUBLIC;PRIVATE;INTERFACE" # MultiValueKeywords
            ${__target_link_depends}
        )

        if(NOT "${__target_link_depends}" STREQUAL "")
            target_link_libraries("${__target}"
                ${__target_link_depends}
            )
        endif()

        if(NOT "${__target_headers}" STREQUAL "" AND
            "${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.23"
        )
            target_sources(
                "${__target}"
                PUBLIC FILE_SET HEADERS
                FILES ${__target_headers}
            )
        endif()

        if(NOT "${__target_modules}" STREQUAL "" AND
            "${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.23"
        )
            target_sources(
                "${__target}"
                PUBLIC FILE_SET CXX_MODULES
                FILES ${__target_modules}
            )
        endif()

        add_dependencies("${__target}" ${__TARGET_DEPENDS})

        if(NOT "${__target_link_options}" STREQUAL "")
            target_link_options("${__target}"
                ${__target_link_options}
            )
        endif()

        if(NOT "${__target_compile_options}" STREQUAL "")
            target_compile_options(
                "${__target}"
                ${__target_compile_options}
            )
        endif()

        if(NOT "${__target_compile_definitions}" STREQUAL "")
            target_compile_definitions(
                "${__target}"
                ${__target_compile_definitions}
            )
        endif()

        if(NOT "${__target_compile_features}" STREQUAL "")
            target_compile_features(
                "${__target}"
                ${__target_compile_features}
            )
        endif()

        if(NOT "${__target_properties}" STREQUAL "")
            set_target_properties("${__target}" PROPERTIES ${__target_properties})
        endif()
    endfunction()
endif()

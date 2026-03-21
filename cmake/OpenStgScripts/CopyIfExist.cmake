# LICENSE : MIT
set(__copy_if_exist_sources "${COPY_IF_EXIST_SOURCE}")
set(__copy_if_exist_target "${COPY_IF_EXIST_TARGET}")

foreach(source IN LISTS __copy_if_exist_sources)
    if(NOT EXISTS "${source}")
        continue()
    endif()

    cmake_path(GET source PARENT_PATH source_dir)
    if(NOT EXISTS "${source_dir}")
        file(MAKE_DIRECTORY "${source_dir}")
    endif()
    
    execute_process(COMMAND "${CMAKE_COMMAND}" "-E" "copy_if_different" "${source}" "${__copy_if_exist_target}")
endforeach()

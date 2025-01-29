find_package(Doxygen QUIET)

if(Doxygen_FOUND)
    
else()
    add_custom_command(doxygen COMMAND FALSE COMMENT "doxygen not found")
endif()

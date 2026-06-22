include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCCompilerFlag)

check_include_file("stdint.h" HAS_STDINT_H)
if(NOT ${HAS_STDINT_H})
    message(FATAL_ERROR "Require <stdint.h>")
endif()


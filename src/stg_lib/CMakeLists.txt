target_sources(open_stg_base_lib
    PRIVATE "${CMAKE_BINARY_DIR}/include/ProjectImformation.h"
)
target_include_directories(open_stg_shared INTERFACE "include-private")
target_include_directories(open_stg_base_lib PUBLIC SYSTEM include)
target_sources(
    open_stg_base_lib
    PUBLIC FILE_SET HEADERS
    FILES
    include/OpenStgCore.h
    include/OpenStgDefine.h
)
target_sources(
    open_stg_base_lib
    PRIVATE
    ElectromagneticDotTimer.c
    GetErrorMessage.c
    ModuleContainer.c
    ProgramStatic.c
    SetError.cpp
    ThreadLocalStorage.c
    UniversalRegistrar.c
    WindowsDllMain.c
    initCore.c
)

target_sources(
    open_stg_graphics_lib
    PUBLIC FILE_SET HEADERS
    FILES
    include/OpenStgGraphics.h
)
target_sources(
    open_stg_graphics_lib
    PRIVATE
    GpInit.c
    GpFormatException.c
)

target_sources(
    open_stg_net_lib
    PUBLIC FILE_SET HEADERS 
    FILES
    include/OpenStgNet.h
)
target_sources(
    open_stg_net_lib
    PRIVATE
    NwInit.c
)
target_include_directories(open_stg_shared INTERFACE include-private)
target_include_directories(open_stg_base_lib PUBLIC SYSTEM include)
target_sources(
    open_stg_base_lib
    PUBLIC FILE_SET HEADERS
    FILES
    include/OpenStg/OpenStgCore.h
    include/OpenStg/OpenStgDefine.h
)
target_sources(
    open_stg_base_lib
    PRIVATE
    ElectromagneticDotTimer.c
    GetErrorMessage.c
    CrModuleContainer.cpp
    ProgramStatic.c
    SetError.cpp
    ThreadLocalStorage.c
    UniversalRegistrar.c
    WindowsDllMain.c
    CrInit.c
)

target_sources(
    open_stg_graphics_lib
    PUBLIC FILE_SET HEADERS
    FILES
    include/OpenStg/OpenStgGraphics.h
)
target_sources(
    open_stg_graphics_lib
    PRIVATE
    gp/GpInit.c
    gp/GpFormatException.c
)

target_sources(
    open_stg_net_lib
    PUBLIC FILE_SET HEADERS
    FILES
    include/OpenStg/OpenStgNet.h
)
target_sources(
    open_stg_net_lib
    PRIVATE
    nw/NwInit.c
)

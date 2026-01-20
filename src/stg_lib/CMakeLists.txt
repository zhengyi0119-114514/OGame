target_sources(open_stg_base_lib
    PRIVATE "${CMAKE_BINARY_DIR}/include/ProjectImformation.h"
)
target_include_directories(open_stg_base_lib PRIVATE "include-private")
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
    ModuleContatiner.c
    OgInit.c
    OgQuit.c
    ProgramStatic.c
    SetError.c
    ThreadLocalStorage.c
    UniversalRegistrar.c
    WindowsDllMain.c
    initCore.c
    inlineFunction.c
)


target_sources(open_stg_lib
    PRIVATE "${CMAKE_BINARY_DIR}/include/ProjectImformation.h"
)
target_include_directories(open_stg_lib PRIVATE "include-private")
target_include_directories(open_stg_lib PUBLIC SYSTEM include)
target_sources(
    open_stg_lib
    PRIVATE FILE_SET HEADERS
    FILES
    include-private/CloseStg.h
    include-private/CloseStgHistory.h
)
target_sources(
    open_stg_lib
    PRIVATE
    ElectromagneticDotTimer.c
    GetErrorMessage.c
    inlineFunctiom.c
    ModuleContatiner.c
    OgInit.c
    OgQuit.c
    ProgramStatic.c
    RegisteredProgram.c
    ThreadLocalStorage.c
    WindowsDllMain.c
)


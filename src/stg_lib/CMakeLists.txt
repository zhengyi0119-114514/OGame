target_sources(open_stg_lib PRIVATE "${CMAKE_BINARY_DIR}/include/ProjectImformation.h")
target_include_directories(open_stg_lib PRIVATE "include-private")
target_include_directories(open_stg_lib INTERFACE SYSTEM include)
target_sources(
    open_stg_lib
    PRIVATE FILE_SET HEADERS 
    FILES
    ./include-private/CloseStg.h
)
target_sources(
    open_stg_lib 
    PRIVATE 
    ./ElectromagneticDotTimer.c
)

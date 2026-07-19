set(CMAKE_SYSTEM_NAME Windows)

if(NOT ("${CMAKE_HOST_SYSTEM_NAME}" MATCHES [=[^(Windows(Phone|Store)?|MSYS$]=]))
    set(CMAKE_C_COMPILER "cc")
    set(CMAKE_CXX_COMPILER "c++")
else()
    set(CMAKE_C_COMPILER "x86_64-w64-mingw32-cc")
    set(CMAKE_CXX_COMPILER "x86_64-w64-mingw32-c++")

endif()

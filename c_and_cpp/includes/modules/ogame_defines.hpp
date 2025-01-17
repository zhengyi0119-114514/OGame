#include <stdint.h>

#ifndef OGAME_HEAD_DEFINES
#define OGAME_HEAD_DEFINES

#ifdef _WIN32
    #define OGAME_API_EXPORT __declspec(dllexport)
    #define OGAME_API_IMPORT __declspec(dllimport)
    #define OGAME_API_EXPORT_WIN32 OGAME_API_EXPORT
    #define OGAME_API_IMPORT_WIN32 OGAME_API_IMPORT
#else
    #define OGAME_API_EXPORT 
    #define OGAME_API_IMPORT extern
    #define OGAME_API_EXPORT_WIN32
    #define OGAME_API_IMPORT_WIN32
#endif

#ifdef OGAME_EXPORT
    #define OGAME_API OGAME_API_EXPORT
    #define OGAME_API_WIN32 OGAME_API_EXPORT_WIN32
#else
    #define OGAME_API OGAME_API_IMPORT
    #define OGAME_API_WIN32 OGAME_API_IMPORT_WIN32
#endif

#define ref_this (*this)

typedef uint32_t OGAME_RESULT;


#endif
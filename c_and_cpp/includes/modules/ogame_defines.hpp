#include <stdint.h>

#ifndef OGAME_HEAD_DEFINES
#define OGAME_HEAD_DEFINES

#ifdef _WIN32
    #define OGAME_API_EXPORT __declspec(dllexport)
    #define OGAME_API_IMPORT __declspec(dllimport)
#else
    #define OGAME_API_EXPORT 
    #define OGAME_API_IMPORT extern
#endif

#ifdef OGAME_EXPORT
    #define OGAME_API OGAME_API_EXPORT
#else
    #define OGAME_API OGAME_API_IMPORT
#endif

#define ref_this (*this)
typedef uint32_t OGAME_RESULT;


#endif
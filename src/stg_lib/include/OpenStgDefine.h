#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include<SDL3/SDL_bits.h>

#if !defined OPEN_GAME_STRUCT_DEFINE_H
#define OPEN_GAME_STRUCT_DEFINE_H 1

#if defined WIN32 || defined WINNT
#define OPEN_STG_EXTERN __declspec(dllimport)
#define OPEN_STG_CDECL __cdecl
#define OPEN_STG_STDCALL __stdcall
#define OPEN_STG_INTERNAL
#define OPEN_STG_PRIVATE static
#else
#define OPEN_STG_EXTERN extern
#define OPEN_STG_CDECL __attribute__((__cdecl__))
#define OPEN_STG_STDCALL __attribute__((__stdcall__))
#define OPEN_STG_INTERNAL __attribute__((visibility("hidden")))
#define OPEN_STG_PRIVATE static
#endif

#if defined __cplusplus
extern "C"
{
#endif

typedef uint64_t OgError;


#if defined __cplusplus
}
#endif
#endif
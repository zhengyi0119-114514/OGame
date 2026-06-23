#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined (OPEN_STG_MACRO_BASE_MEMORY_H)
#define OPEN_STG_MACRO_BASE_MEMORY_H 1
OG_MACRO_C_BLOCK_BEGIN

struct OgModule;
struct OgDynamicArray;
struct OgDependencyTree;
struct OgAllocator;
struct OgDependencyTree;
struct OgStringEx;
struct OgException;
struct OgExceptionBasicDebugImformation;
struct OgFunction;
struct OgDebugSource;

typedef const char OgConstCharacter, *OgConstString;
typedef char OgCharacter, *OgString;
typedef int8_t OgSignedInteger8, OgInteger8, OgSignedByte, OgSByte;
typedef uint8_t OgUnsignedInteger8, OgUnsignedByte, OgByte;
typedef int16_t OgSignedInteger16, OgInteger16;
typedef uint16_t OgUnsignedInteger16;
typedef int32_t OgSignedInteger32, OgInteger32;
typedef uint32_t OgUnsignedInteger32;
typedef int64_t OgSignedInteger64, OgInteger64;
typedef uint64_t OgUnsignedInteger64;
typedef int64_t OgSignedIntegerSize;
typedef uint64_t OgUnsignedIntegerSize;
typedef intptr_t OgIntPtr, OgPointerSizedSignedInteger;
typedef uintptr_t OgUIntPtr, OgPointerSizedUnsignedInteger;
typedef uint8_t OgBoolean;
typedef void *OgPVoid;

#define OgTrue true
#define OgFalse false
#define OPEN_STG_MODULE_REGISTERED_NAME "IceThorn.OpenStg.Base.SB"

OG_MACRO_C_BLOCK_END
#endif

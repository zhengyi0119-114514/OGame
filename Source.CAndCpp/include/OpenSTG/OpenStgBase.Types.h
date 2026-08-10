#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>
#include <stdalign.h>
#include <stdbool.h>

#if !defined(OPEN_STG_MACRO_BASE_MEMORY_H)
#define OPEN_STG_MACRO_BASE_MEMORY_H 1
#include <OpenSTG/OpenStgBase.Macro.h>
OgMacroCBlockBegin

struct OgModule;
struct OgDynamicArray;
struct OgDependencyTree;
struct OgThread;
struct OgTask;
struct OgResult;
struct OgExceptionInformation;
struct OgExceptionDebugInformation;
struct OgExceptionStructureOutOfRange;
struct OgExceptionStructureInvalidArgument;
struct OgExceptionStructureUndefineBehavior;
struct OgExceptionStructureFormatException;
struct OgExceptionStructureMemoryException;
struct OgExceptionCollectionFormatException;
struct OgExceptionCollectionIoException;
typedef enum OgEnumBitFlagOperator
{
    OgEnumBitFlagOperatorItemAnd = 0,
    OgEnumBooleanOperatorItemOr = 1,
} OgEnumBitFlagOperator;

struct OgDebugSource;
struct OgAllocator;
struct OgIoStteam;

typedef const char OgConstantCharacter, *OgConstantString;
typedef const char *OgConstantString;
typedef char OgCharacter, *OgString;
typedef signed char OgSignedCharater;
typedef unsigned char OgUnsignedCharater;
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
typedef void *OgPVoid;

typedef uint8_t OgBoolean, Og8BitBoolean;
typedef uint32_t Og32BitBoolean;
#define OgFalse false
#define OgTrue true
#define OgBooleanFalse UINT8_C(0)
#define OgBooleanTrue UINT8_C(1)
#define Og8BitBooleanFalse UINT8_C(0)
#define Og8BitBooleanTrue UINT8_C(1)
#define Og32BitBooleanFalse UINT32_C(0)
#define Og32BitBooleanTrue UINT32_C(1)

#define OgMacroSignedInteger8Constant(Value) INT8_C(Value)
#define OgMacroUnsignedInteger8Constant(Value) UINT8_C(Value)
#define OgMacroSignedInteger16Constant(Value) INT16_C(Value)
#define OgMacroUnsignedInteger16Constant(Value) UINT16_C(Value)
#define OgMacroSignedInteger32Constant(Value) INT32_C(Value)
#define OgMacroUnsignedInteger32Constant(Value) UINT32_C(Value)
#define OgMacroSignedInteger64Constant(Value) INT64_C(Value)
#define OgMacroUnsignedInteger64Constant(Value) UINT64_C(Value)
#define OgMacroSignedIntegerSizeConstant(Value) INT64_C(Value)
#define OgMacroUnsignedIntegerSizeConstant(Value) UINT64_C(Value)

OgMacroCBlockEnd
#endif

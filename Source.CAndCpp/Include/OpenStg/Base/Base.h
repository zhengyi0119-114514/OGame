#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <uchar.h>
#include <assert.h>

#if __has_include("OpenStgBase.Options.h")
#include <OpenStgBase.Options.h>
#endif
#if !defined(OgBaseMacroHeaderTagBase)
#define OgBaseMacroHeaderTagBase 1
#if defined(_MSC_VER)
#define OgMacroMsvc(...) __VA_ARGS__
#define OgMacroMsvcDeclspec(Expression) __declspec(Expression)
#define OgMacroGnu(...)
#define OgMacroGnuAttribute(...)
#define OgMacroAlwaysInline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define OgMacroMsvc(...)
#define OgMacroMsvcDeclspec(Expression)
#define OgMacroGnu(...) __VA_ARGS__
#define OgMacroGnuAttribute(...) __attribute__((__VA_ARGS__))
#define OgMacroAlwaysInline __attribute__((__always_inline__))
#endif
#if defined(__cplusplus)
#define OgMacroC(...)
#define OgMacroCpp(...) __VA_ARGS__
#define OgMacroCBlockBegin \
    extern "C" \
    {
#define OgMacroCBlockEnd }
#else
#define OgMacroC(...) __VA_ARGS__
#define OgMacroCpp(...)
#define OgMacroCBlockBegin
#define OgMacroCBlockEnd
#endif
#if defined(__cplusplus) && __cplusplus >= 201103L
#define OgNullPtr nullptr
#elif defined(__cplusplus)
#define OgNullPtr 0L
#else
#define OgNullPtr ((OgPVoid)0)
#endif

OgMacroCBlockBegin

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

#define OgConstantSingedIntegerSizeMax OgMacroSignedIntegerSizeConstant(0x00FFFFFFFFFFFFFF)

typedef const char OgConstantCharacter, *OgConstantString;
typedef const char *OgConstantString;

#if defined (OgMacroOptionsEnableUnicode) && OgMacroOptionsEnableUnicode 
typedef const wchar_t OgConstantWidthCharacter, *OgConstantWidthString;
typedef wchar_t OgWidthCharacter, *OgWidthString;
#if defined(__cplusplus) && defined(__cpp_char8_t)
typedef const char8_t OgConstantUtf8Character, *OgConstantUtf8String;
typedef char8_t OgUtf8Character, *OgUtf8String;
#else
typedef const char OgConstantUtf8Character, *OgConstantUtf8String;
typedef char OgUtf8Character, *OgUtf8String;
#endif
typedef const char16_t OgConstantUtf16Character, *OgConstantUtf16String;
typedef char16_t OgUtf16Character, *OgUtf16String;
typedef const char32_t OgConstantUtf32Character, *OgConstantUtf32String;
typedef char32_t OgUtf32Character, *OgUtf32String;
#endif

OgMacroCBlockEnd
#endif

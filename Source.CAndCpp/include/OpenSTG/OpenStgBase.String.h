#include <string.h>
#include <stdlib.h>
#if !defined(OPEN_STG_MACRO_BASE_STRING_H)
#define OPEN_STG_MACRO_BASE_STRING_H 1
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
OG_MACRO_C_BLOCK_BEGIN


inline OgBoolean OgStringIsNullOrEmpty(OgConstantString pcsString);
typedef struct OgStringEx
{
    OgString String;
    OgUnsignedIntegerSize StringSize;
    struct OgConstantAllocator *Allocator;
} OgStringEx;

OG_MACRO_EXTERN OgExceptionFormattingException OgStringCopy(
    OgString psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatersToCopy);
OG_MACRO_EXTERN OgExceptionFormattingException OgStringConnect(
    OgString psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatersToConnect);

#define OgStringGetEmptyString() ""

OG_MACRO_C_BLOCK_END
#if !defined (OPEN_STG_MACRO_BASE_STRING_INLINE_H)
#include <OpenSTG/OpenStgBase.String.Inline.h>
#endif
#endif

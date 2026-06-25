#include <string.h>
#include <stdlib.h>
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
#if !defined(OPEN_STG_MACRO_BASE_STRING)
#define OPEN_STG_MACRO_BASE_STRING 1
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
#include <OpenSTG/OpenStgBase.String.Inline.h>
#endif

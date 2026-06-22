#include <string.h>
#include <stdlib.h>
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
#if !defined(OPEN_STG_MACRO_BASE_STRING)
#define OgStringGetEmptyString() ""
#define OPEN_STG_MACRO_BASE_STRING 1
OG_MACRO_C_BLOCK_BEGIN

typedef struct OgStringEx
{
    OgString String;
    OgUnsignedIntegerSize StringSize;
    const struct OgAllocator *Allocator;
} OgStringEx;
OG_MACRO_EXTERN OgException OgStringCopy(
    OgConstString pcsSource,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize);
OG_MACRO_EXTERN OgException OgStringConnect(
    OgString psDestination,
    OgUnsignedIntegerSize iDestinationSize,
    OgConstString pcsSource);
OG_MACRO_EXTERN OgException OgStringConvert(
    OgConstString pcsSource,
    OgConstString pcsSourceEncoding,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize,
    OgConstString pcsDestinationEncoding);
OG_MACRO_EXTERN OgException OgStringGetConversionLength(
    OgConstString pcsSource,
    OgConstString pcsSourceEncoding,
    OgConstString pcsDestinationEncoding,
    OgUnsignedIntegerSize puDestinationSize);
OG_MACRO_EXTERN OgException OgStringExCreate(
    OgStringEx *pString,
    OgSignedIntegerSize uSize,
    OgConstString pcsContent);
OG_MACRO_EXTERN OgException OgStringExGetLength(
    OgStringEx *psString,
    OgUnsignedIntegerSize *puStringLength);
OG_MACRO_EXTERN OgException OgStringExGetData(
    OgStringEx *psString,
    OgString *ppsData);
OG_MACRO_EXTERN OgException OgStringExConnect(
    OgStringEx *pString,
    OgConstString *pcsSource);
OG_MACRO_EXTERN OgException OgStringExDestroy(OgStringEx *psString);

inline OgString OgStringAllocMemoryAndInitialize(OgUnsignedIntegerSize uLength);
inline OgString OgStringAllocMemoryAndClone(OgConstString pcsSource);
inline void OgStringFree(OgString psString);

OG_MACRO_C_BLOCK_END
#include <OpenSTG/OpenStgBase.String.Inline.h>
#endif

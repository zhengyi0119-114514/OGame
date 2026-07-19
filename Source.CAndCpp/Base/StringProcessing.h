#include <OpenSTG/OpenStgBase.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#if !defined(OPEN_STG_STRING_PROCESSING_H)
#define OPEN_STG_STRING_PROCESSING_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_EXPORT struct OgExceptionCollectionFormatException OgStringCopy(
    OgString const psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString const pcsSource,
    OgSignedInteger64 iCharatersToCopy);
OG_MACRO_EXPORT struct OgExceptionCollectionFormatException OgStringConnect(
    OgString const psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString const pcsSource,
    OgSignedInteger64 iCharatersToConnect);

OG_MACRO_C_BLOCK_END
#endif

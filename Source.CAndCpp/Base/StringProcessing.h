#include <OpenSTG/OpenStgBase.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#if !defined(OPEN_STG_STRING_PROCESSING_H)
#define OPEN_STG_STRING_PROCESSING_H 1
OgMacroCBlockBegin

OgMacroExport struct OgExceptionCollectionFormatException OgStringCopy(
    OgString const psDestination,
    OgSignedIntegerSize iDestinationSize,
    OgConstantString const pcsSource,
    OgSignedIntegerSize iCharatersToCopy
);
OgMacroExport struct OgExceptionCollectionFormatException OgStringConnect(
    OgString const psDestination,
    OgSignedIntegerSize iDestinationSize,
    OgConstantString const pcsSource,
    OgSignedIntegerSize iCharatersToConnect
);

OgMacroCBlockEnd
#endif

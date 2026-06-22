#include <OpenSTG/OpenStgBase.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#if !defined(OPEN_STG_STRING_PROCESSING_H)
#define OPEN_STG_STRING_PROCESSING_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_EXPORT OgException OgStringCopy(OgConstString pcsSource, OgString psDestination, OgUnsignedIntegerSize iDestinationSize);
OG_MACRO_EXPORT OgException OgStringConcatenation(OgString psDestination,OgUnsignedIntegerSize iDestinationSize,OgConstString pcsSource);

OG_MACRO_C_BLOCK_END
#endif

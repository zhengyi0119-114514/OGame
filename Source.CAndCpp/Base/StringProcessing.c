#include "StringProcessing.h"
#include "Exception.h"
#if OPEN_STG_MACRO_USE_LIBBSD
#include <bsd/string.h>
#include <errno.h>
#elif OPEN_STG_MACRO_USE_LIBSAFEC
#include <errno.h>
#include <safeclib/safec.h>
#elif OPEN_STG_MACRO_USE_STDC
#define __STDC_WANT_LIB_EXT1__ 1
#include <errno.h>
#include <string.h>
#endif

OgExceptionFormattingException OgStringCopy(
    OgString psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatersToCopy)
{
    if(iDestinationSize <= 0 && iCharatersToCopy <= 0 )
    {
        
    }
}
OgExceptionFormattingException OgStringConnect(
    OgString psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatersToConnect);

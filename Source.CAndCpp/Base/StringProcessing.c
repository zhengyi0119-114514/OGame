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

OgException OgStringCopy(
    OgConstString pcsSource,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize)
{
#if OPEN_STG_MACRO_USE_LIBBSD
    size_t uSourceSize = strlcpy(psDestination, pcsSource, uDestinationSize);
    if (uSourceSize >= uDestinationSize)
    {
        return OgExceptionThrowOutOfRange("uDestinationSize", OgStringGetEmptyString(), OgStringGetEmptyString());
    }
#elif OPEN_STG_MACRO_USE_STDC || OPEN_STG_MACRO_USE_LIBSAFEC
    if (strcpy_s(psDestination, iDestinationSize, pcsSource) != 0)
    {
        return OgExceptionThrowOutOfRange("uDestinationSize", OgStringGetEmptyString(), OgStringGetEmptyString());
    }
#else
    static_assert(false, "Require libbsd ,libsafec or Annex K Stdandard C library");
#endif
    return OgExceptionThrowNothing();
}
OgException OgStringConcatenation(
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize,
    OgConstString pcsSource)
{
#if OPEN_STG_MACRO_USE_LIBBSD
    if (strlcat(psDestination, pcsSource, uDestinationSize) >= uDestinationSize)
    {
        return OgExceptionThrowOutOfRange("uDestinationSize", OgStringGetEmptyString(), OgStringGetEmptyString());
    }
#elif OPEN_STG_MACRO_USE_STDC || OPEN_STG_MACRO_USE_LIBSAFEC
    if (strcat_s(psDestination, uDestinationSize, pcsSource) != 0)
    {
        return OgExceptionThrowOutOfRange("uDestinationSize", OgStringGetEmptyString(), OgStringGetEmptyString());
    }
#else
    static_assert(false, "Require libbsd ,libsafec or Annex K Stdandard C library");
#endif
    return OgExceptionThrowNothing();
}

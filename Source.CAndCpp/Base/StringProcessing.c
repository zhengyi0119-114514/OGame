#include "StringProcessing.h"
#include "Exception.h"
#include "InlineFunctions.h"
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

struct OgExceptionCollectionFormatException OgStringCopy(
    OgString const psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString const pcsSource,
    OgSignedInteger64 iCharatersToCopy
)
{
    struct OgExceptionCollectionFormatException e = {};
    if (OgPrivateIsNull(psDestination))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgString psDestination", "Argument is NULL."
        );
        return e;
    }
    if (OgPrivateIsNull(pcsSource))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgConstantString pcsSource", "Argument is NULL."
        );
        return e;
    }
    if (iDestinationSize == 0)
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgSignedInteger64 iDestinationSize", "iDestinationSize is zero."
        );
        return e;
    }
    if (iCharatersToCopy == 0)
    {
        return e;
    }
    if (iDestinationSize <= 0 && iCharatersToCopy <= 0)
    {
        strcpy(psDestination, pcsSource);
        return (e);
    }
    else if (iDestinationSize > 0 && iCharatersToCopy <= 0)
    {
#if OPEN_STG_MACRO_USE_LIBBSD
        if (strlcpy(psDestination, pcsSource, (size_t)iDestinationSize) >= (size_t)iDestinationSize)
        {
            memset(psDestination, 0, (size_t)iDestinationSize);
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)strlen(pcsSource) + 1, "The string 'psDestination' is to short."
            );
            return e;
        }
#elif OPEN_STG_MACRO_USE_STDC || OPEN_STG_MACRO_USE_LIBSAFEC
        if (strcpy_s(psDestination, (rsize_t)iDestinationSize, pcsSource) != 0)
        {
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)strlen(pcsSource) + 1, "The string 'psDestination' is to short."
            );
            return e;
        }
        /// TODO: finish it.
#endif
    }
    else if (iDestinationSize <= 0 && iCharatersToCopy > 0)
    {
        strncpy(psDestination, pcsSource, (size_t)iCharatersToCopy);
    }
    else if (iDestinationSize > 0 && iCharatersToCopy > 0)
    {
        size_t uRealCharatersToCopy =
            (size_t)OgPrivateSizeTMin(strlen(pcsSource), (size_t)iCharatersToCopy);
        if (uRealCharatersToCopy >= (size_t)iDestinationSize)
        {
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)uRealCharatersToCopy, "The string 'psDestination' is too short."
            );
            return e;
        }
        strncpy(psDestination, pcsSource, uRealCharatersToCopy);
    }
    return e;
}
OG_MACRO_EXPORT struct OgExceptionCollectionFormatException OgStringConnect(
    OgString psDestination,
    OgSignedInteger64 iDestinationSize,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatersToConnect
)
{

    struct OgExceptionCollectionFormatException e = {};
    if (OgPrivateIsNull(psDestination))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgString psDestination", "Argument is NULL."
        );
        return e;
    }
    if (OgPrivateIsNull(pcsSource))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgConstantString pcsSource", "Argument is NULL."
        );
        return e;
    }
    if (iDestinationSize == 0)
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgSignedInteger64 iDestinationSize", "iDestinationSize is zero."
        );
        return e;
    }
    if (iCharatersToConnect == 0)
    {
        return e;
    }
    if (iDestinationSize <= 0 && iCharatersToConnect <= 0)
    {
        strcat(psDestination, pcsSource);
        return (e);
    }
    else if (iDestinationSize > 0 && iCharatersToConnect <= 0)
    {
#if OPEN_STG_MACRO_USE_LIBBSD
        size_t uStringLenth = strlen(psDestination);
        if (strlcat(psDestination, pcsSource, (size_t)iDestinationSize) >= (size_t)iDestinationSize)
        {
            psDestination[uStringLenth] = '\0';
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)strlen(pcsSource) + 1, "The string 'psDestination' is to short."
            );
            return e;
        }
#elif OPEN_STG_MACRO_USE_STDC || OPEN_STG_MACRO_USE_LIBSAFEC
        // TODO: finish it
        if (strcat_s(psDestination, (size_t)iDestinationSize, pcsSource) != 0)
        {
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)strlen(pcsSource) + 1, "The string 'psDestination' is to short."
            );
            return e;
        }
#endif
    }
    else if (iDestinationSize <= 0 && iCharatersToConnect > 0)
    {
        strncat(psDestination, pcsSource, (size_t)iCharatersToConnect);
    }
    else if (iDestinationSize > 0 && iCharatersToConnect > 0)
    {
#if OPEN_STG_MACRO_USE_STDC || OPEN_STG_MACRO_USE_LIBSAFEC
        if (strncat_s(
                psDestination, (size_t)iDestinationSize, pcsSource, (size_t)iCharatersToConnect
            ) != 0)
        {
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)iDestinationSize, "The string 'psDestination' is to short."
            );
            return e;
        }
#else
        size_t uDestinationStringLength = strlen(psDestination);
        size_t uRealCharatersToConnect =
            OgPrivateSizeTMin(strlen(pcsSource), (size_t)iCharatersToConnect);
        size_t uNewStringLength = uDestinationStringLength + uRealCharatersToConnect;
        if (uNewStringLength >= (size_t)iDestinationSize)
        {
            e.Type = OgExceptionEnumFormatingExceptionItemOutOfRange;
            e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
                "OgString psDestination,OgSignedInteger64 iDestinationSize", INT64_MAX,
                (OgSignedInteger64)uNewStringLength, "The string 'psDestination' is to short."
            );
            return e;
        }
        strncat(psDestination, pcsSource, uRealCharatersToConnect);
#endif
    }
    return e;
}

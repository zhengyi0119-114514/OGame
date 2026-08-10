#include "Exception.h"
#include "InlineFunctions.h"
#include <stdio.h>
#define OUT_OF_RANGE_FORMAT_STRING "%d"

static const struct OgExceptionInformation s_eiOutOfRangeExcerptionInformation = {
    OgPrivateExceptionStructureOutOfRangeFormatMessage,
    OgPrivateExceptionStructureOutOfRangeGetExceptionMessageLength,
    OgPrivateExceptionStructureOutOfRangeSerialize,
    OgPrivateExceptionStructureOutOfRangeDeserialize,
    OgPrivateExceptionStructureOutOfRangeGetExceptionName,
};
OgMacroPrivate OgConstantString OgPrivateExceptionStructureOutOfRangeGetExceptionName(
    void
)
{
    return ("OpenStg.Base.Exception.OutOfRangeException");
}
struct OgExceptionCollectionFormatException OgPrivateExceptionStructureOutOfRangeFormatMessage(
    OgPVoid pvExceptionSource,
    OgUnsignedIntegerSize uDestinationBufferSize,
    OgString psDestinationBuffer
);
struct OgExceptionCollectionFormatException
    OgPrivateExceptionStructureOutOfRangeGetExceptionMessageLength(
        OgPVoid pvExceptionSource, OgUnsignedIntegerSize *const puMessageLength
    )
{
    struct OgExceptionCollectionFormatException e = {};
    struct OgExceptionStructureOutOfRange *oor =
        (struct OgExceptionStructureOutOfRange *)pvExceptionSource;
    if (OgPrivateIsNull(pvExceptionSource))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgPVoid pvExceptionSource", "Argument is null."
        );
        return e;
    }
    if (OgPrivateIsNull(puMessageLength))
    {
        e.Type = OgExceptionEnumFormatingExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgUnsignedInteger64 *const puMessageLength", "Argument is null."
        );
        return e;
    }
    *puMessageLength =
        (OgUnsignedIntegerSize)snprintf(NULL, 0, OUT_OF_RANGE_FORMAT_STRING, oor->Description);
    return e;
}
struct OgExceptionCollectionFormatException OgPrivateExceptionStructureOutOfRangeSerialize(
    OgPVoid pvExceptionSource,
    OgPVoid pvDestinationBuffer,
    OgUnsignedIntegerSize puDestinationBufferSize
);
struct OgExceptionCollectionFormatException OgPrivateExceptionStructureOutOfRangeDeserialize(
    OgPVoid pvDestinationBuffer,
    OgUnsignedIntegerSize puDestinationBufferSize,
    OgPVoid pvSourceBuffer,
    OgUnsignedIntegerSize puSourceBufferSize
);
OgMacroExtern const struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(
    void
)
{
    return &s_eiOutOfRangeExcerptionInformation;
};

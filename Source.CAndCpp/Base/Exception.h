#include <OpenSTG/OpenStgBase.h>
#if !defined(OPEN_STG_EXCEPTION_H)
#define OPEN_STG_EXCEPTION_H 1
#define OPEN_STG_CONST_MINIMUN_STRING_LENGTH 64
#define OPEN_STG_CONST_MAXIMUN_STRING_LENGTH 64

OG_MACRO_EXPORT OgExceptionFormattingException OgExceptionOutOfRangeFormatExceptionMessage(
    struct OgExceptionStructureOutOfRange *poorException,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgString psDestinationBuffer);
OG_MACRO_EXPORT OgExceptionFormattingException OgExceptionOutOfRangeGetExceptionMessageLength(
    struct OgExceptionStructureOutOfRange *poorException,
    OgUnsignedInteger64 *const puMessageLength);
inline OgExceptionFormattingException OgExceptionOutOfRangeFormatExceptionMessageWarpper(
    OgPVoid pvExceptionSource,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgString psDestinationBuffer)
{
    return OgExceptionOutOfRangeFormatExceptionMessage(
        (struct OgExceptionStructureOutOfRange *)pvExceptionSource, uDestinationBufferSize,
        psDestinationBuffer);
}
inline OgExceptionFormattingException OgExceptionOutOfRangeGetExceptionMessageLengthWrapper(
    OgPVoid pvExceptionSource, OgUnsignedInteger64 *const puMessageLength)
{
    return OgExceptionOutOfRangeGetExceptionMessageLength(
        (struct OgExceptionStructureOutOfRange *)pvExceptionSource, puMessageLength);
}
OG_MACRO_PRIVATE OgExceptionFormattingException OgExceptionOutOfRangeSerializeWrapper(
    OgPVoid pvExceptionSource,
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize);

/// TODO: After default serialize.
OG_MACRO_PRIVATE OgExceptionFormattingException OgExceptionOutOfRangeDeserializeWrapper(
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize,
    OgPVoid pvSourceBuffer,
    OgUnsignedInteger64 puSourceBufferSize);
/// TODO: After default serialize.
OG_MACRO_PRIVATE OgConstantString OgExceptionOutOfRangeGetExceptionName();
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureInvalidArgumentGetInformation(
    void);
#endif

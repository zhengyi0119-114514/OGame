#include <OpenSTG/OpenStgBase.h>
#if !defined(OPEN_STG_EXCEPTION_H)
#define OPEN_STG_EXCEPTION_H 1
#define OPEN_STG_CONST_MINIMUN_STRING_LENGTH 64
#define OPEN_STG_CONST_MAXIMUN_STRING_LENGTH 64

typedef enum OgExceptionDefaultType
{
    OgExceptionTypeNull = 0,
    OgExceptionTypeLogicException = 0x00010000,
    OgExceptionTypeOutOfRange = OgExceptionTypeLogicException + 1,
    OgExceptionTypeArgumentNull = OgExceptionTypeOutOfRange + 1,
    OgExceptionTypeInvalidArgument = OgExceptionTypeArgumentNull + 1,
    OgExceptionTypeInvalidOperation = OgExceptionTypeInvalidArgument + 1,
    OgExceptionTypeFormat = OgExceptionTypeInvalidOperation + 1,
    OgExceptionTypeRuntimeException = 0x00020000,
    OgExceptionTypeOutOfMemory = OgExceptionTypeRuntimeException + 1,
    OgExceptionTypeStackOverflow = OgExceptionTypeOutOfMemory + 1,
} OgExceptionDefaultType;

typedef struct
{
    OgExceptionDefaultType Type;
    OgExceptionBasicDebugInformation Basic;
    OgCharacter Maximun[OPEN_STG_CONST_MAXIMUN_STRING_LENGTH];
    OgCharacter Minimun[OPEN_STG_CONST_MINIMUN_STRING_LENGTH];
} OgPrivateExceptionOutOfRangeException;
OG_MACRO_EXPORT OgException OgExceptionThrowOutOfRangeV(
    OgConstString pcsParameter,
    OgConstString pcsMin,
    OgConstString pcsMax);
OG_MACRO_EXPORT OgException OgExceptionThrowOutOfRangeD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter,
    OgConstString pcsMin,
    OgConstString pcsMax);

OG_MACRO_NORETURN void OgExceptionPanic(OgException e);
OG_MACRO_PRIVATE void OgPrivateExceptionOutOfRangeDestroy(struct OgException e);
OG_MACRO_PRIVATE OgException OgPrivateExceptionOutOfRangeFormatMessage(
    const struct OgException eException,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize);
OG_MACRO_PRIVATE OgException OgPrivateExceptionOutOfRangeGetFormattedMessageLength(
    const struct OgException e,
    OgUnsignedIntegerSize *puMessageSize);
OG_MACRO_PRIVATE OgBoolean OgPrivateExceptionLogicExceptionIsSomething(OgConstString pcsTypeName);
OG_MACRO_PRIVATE OgBoolean OgPrivateExceptionOutOfRangeIsSomething(OgConstString pcsTypeName);
#endif

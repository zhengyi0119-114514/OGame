#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTIONS_H)
#define OPEN_STG_MACRO_BASE_EXCEPTIONS_H 1

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H)
#include <OpenSTG/OpenStgBase.Exceptions.Structures.h>
#endif

OG_MACRO_C_BLOCK_BEGIN
typedef enum OgExceptionEnumFormattingExceptionType
{
    OgExceptionEnumFormatingExceptionItemNone = 0,
    OgExceptionEnumFormatingExceptionItemInvalidArgument = 1,
    OgExceptionEnumFormatingExceptionItemOutOfRange = 2,
    OgExceptionEnumFormatingExceptionItemUndefineBehavior = 3,
} OgExceptionEnumFormattingExceptionType;

typedef struct OgExceptionCollectionFormattingException
{
    OgExceptionEnumFormattingExceptionType Type;
    union
    {
        OgExceptionStructureOutOfRange OutOfRange;
        OgExceptionStructureInvalidArgument InvalidArgument;
        OgExceptionStructureUndefineBehavior UndefineBehavior;
    };
} OgExceptionFormattingException;

OG_MACRO_EXTERN OgExceptionFormattingException OgExceptionFormattingExceptionThrowNone(void);
OG_MACRO_EXTERN OgExceptionFormattingException OgExceptionFormattingExceptionThrowInvalidArgument();
OG_MACRO_EXTERN OgExceptionFormattingException
    OgExceptionFormattingExceptionThrowUndefineBehavior();
OG_MACRO_EXTERN OgExceptionFormattingException OgExceptionFormattingExceptionThrowOutOfRange();

typedef OgExceptionFormattingException (*OgExceptionFunctionDefinitionFormatExceptionMessage)(
    OgPVoid pvExceptionSource,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgString psDestinationBuffer);
typedef OgExceptionFormattingException (*OgExceptionFunctionDefinitionGetExceptionMessageLength)(
    OgPVoid pvExceptionSource, OgUnsignedInteger64 *const puMessageLength);
typedef OgExceptionFormattingException (*OgExceptionFunctionDefinitionSerialize)(
    OgPVoid pvExceptionSource,
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize);
typedef OgExceptionFormattingException (*OgExceptionFunctionDefinitionDeserialize)(
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize,
    OgPVoid pvSourceBuffer,
    OgUnsignedInteger64 puSourceBufferSize);
typedef OgConstantString (*OgExceptionFunctionDefinitionGetExceptionName)();

typedef struct OgExceptionInformation
{
    OgExceptionFunctionDefinitionFormatExceptionMessage FormatMessage;
    OgExceptionFunctionDefinitionGetExceptionMessageLength GetExceptionMessageLength;
    OgExceptionFunctionDefinitionSerialize Serialize;
    OgExceptionFunctionDefinitionDeserialize Deserialize;
    OgExceptionFunctionDefinitionGetExceptionName GetExceptionName;
} OgExceptionInformation;

OG_MACRO_NORETURN OG_MACRO_EXTERN void OgExceptionPanic(OgConstantString pcsDescription);
// #define OgExceptionThrowNothing() OgExceptionCreate(0, NULL, NULL)
// #define OgExceptionThrowLogicException OgExceptionThrowLogicExceptionV
// #define OgExceptionThrowOutOfRange OgExceptionThrowOutOfRangeV
// #define OgExceptionThrowInvalidArgument OgExceptionThrowInvalidArgumentV
// #define OgExceptionThrowArgumentNull OgExceptionThrowArgumentNullV
// #define OgExceptionThrowInvalidOperation OgExceptionThrowInvalidOperationV
// #define OgExceptionThrowFormatException OgExceptionThrowFormatExceptionV
// #define OgExceptionThrowRuntimeException OgExceptionThrowRuntimeExceptionV
// #define OgExceptionThrowOutOfMemory OgExceptionThrowOutOfMemoryV
// #define OgExceptionThrowStackOverflow OgExceptionThrowStackOverflowV

OG_MACRO_C_BLOCK_END

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H)
#include <OpenSTG/OpenStgBase.Exceptions.Inline.h>
#endif

#endif

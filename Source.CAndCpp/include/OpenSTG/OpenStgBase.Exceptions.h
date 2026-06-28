#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTIONS_H)
#define OPEN_STG_MACRO_BASE_EXCEPTIONS_H 1
#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H)
#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#endif

OG_MACRO_C_BLOCK_BEGIN

typedef struct OgExceptionDebugInformation
{
    OgUnsignedInteger64 Line;
    OgConstantString File;
    OgConstantString Function;
    OgPVoid Callstack[32];
} OgExceptionDebugInformation;

typedef struct OgExceptionStructureOutOfRange
{
    struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgCharacter MaximumValue[32];
    OgCharacter MinimumValue[32];
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureOutOfRange;

inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreateWithInteger64(
    OgConstantString pcsParamenter,
    OgSignedInteger64 iMaximumValue,
    OgSignedInteger64 iMinimumValue,
    OgConstantString pcsDescription);
inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreate(
    OgConstantString pcsParamenter,
    OgConstantString pcsMaximumValue,
    OgConstantString pcsMinimumValue,
    OgConstantString pcsDescription);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(void);

typedef struct OgExceptionStructureInvalidArgument
{
    struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureInvalidArgument;
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureInvalidArgumentGetInformation(
    void);
inline struct OgExceptionStructureInvalidArgument OgExceptionStructureInvalidArgumentCreate(
    OgConstantString pcsParamenter, OgConstantString pcsDescription);

typedef struct OgExceptionStructureUndefineBehavior
{
    struct OgExceptionInformation *Information;
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureUndefineBehavior;

inline struct OgExceptionStructureUndefineBehavior OgExceptionStructureUndefineBehaviorCreate(
    OgConstantString pcsDescription);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void);

typedef struct OgExceptionStructureFormatException
{
    struct OgExceptionInformation *Information;
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureFormatException;

typedef struct OgExceptionStructureStackOverflow
{
    OgUnsignedInteger64 ProcessId;
    OgUnsignedInteger64 ThreadId;
    OgPointerSizedUnsignedInteger Address;
    OgConstantString Description;
} OgExceptionStructureStackOverflow;

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

typedef enum OgExceptionEnumIoExceptionType
{
    OgExceptionEnumIoExceptionItemNone = 0,
    OgExceptionEnumIoExceptionItemInvalidArgument = 1,
    OgExceptionEnumIoExceptionItemUndefineBehavior = 2,
} OgExceptionEnumIoExceptionType;
typedef struct 
{
    enum OgExceptionEnumIoExceptionType Type;
    union
    {
        struct OgExceptionStructureInvalidArgument InvalidArgument;
        struct OgExceptionStructureUndefineBehavior UndefineBehavior;
    };
} OgExceptionIoException;

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

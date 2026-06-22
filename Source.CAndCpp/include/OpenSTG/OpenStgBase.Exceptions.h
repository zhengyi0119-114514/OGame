#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG__MACRO_BASE_EXCEPTIONS_H)
#define OPEN_STG__MACRO_BASE_EXCEPTIONS_H 1
OG_MACRO_C_BLOCK_BEGIN

#define OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT                                                \
    OgUnsignedInteger64 uLine, OgConstString pcsFile, OgConstString pcsFunction
#define OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT __LINE__, __FILE__, OG_MACRO_FUNCTION
#define OPEN_STG_CONST_CALL_STACK_SIZE 128
#define OgExceptionCreateBasicDebugInformation(bdBasicDebugInformation)                            \
    do                                                                                             \
    {                                                                                              \
        (bdBasicDebugInformation).File = pcsFile;                                                  \
        (bdBasicDebugInformation).Function = pcsFunction;                                          \
        (bdBasicDebugInformation).Line = uLine;                                                    \
        OgExceptionCreateCallStack(                                                                \
            (bdBasicDebugInformation).CallStack, OPEN_STG_CONST_CALL_STACK_SIZE);                  \
    } while (false);

typedef struct OgException
{
    const struct OgExceptionInformation *Information;
    OgPVoid AdditionalData;
} OgException;

typedef struct OgExceptionInformation
{
    void (*ExceptionDestroy)(struct OgException e);
    OgException (*ExceptionFormatMessage)(
        const struct OgException *peException,
        OgString psDestination,
        OgUnsignedIntegerSize uDestinationSize);
    OgException (*ExceptionGetFormattedMessageSize)(
        const struct OgException *peException,
        OgUnsignedIntegerSize *puMessageSize);
    OgException (*ExceptionSerialization)(
        const struct OgException *peException,
        OgUnsignedByte *pbDestinationBuffer,
        OgUnsignedIntegerSize uDestinationBufferSize,
        OgUnsignedIntegerSize *puDestinationChanged);
    OgException (*ExceptionDeserialization)(
        struct OgException *peExceptionOutput,
        const OgUnsignedByte *pbSource,
        OgUnsignedIntegerSize uSourceSize);
    OgConstString (*ExceptionGetExceptionTypeName)(void);
    OgBoolean (*ExceptionIsSomething)(OgConstString pcsTypeName);
} OgExceptionInformation;

typedef struct OgExceptionBasicDebugInformation
{
    OgUnsignedInteger64 Line;
    OgPVoid CallStack[OPEN_STG_CONST_CALL_STACK_SIZE];
    OgConstString File;
    OgConstString Function;
} OgExceptionBasicDebugInformation;

inline OgException OgExceptionCreate(
    const struct OgExceptionInformation *peiInformation,
    OgPVoid pvAdditionalData);
inline OgBoolean OgExceptionSerializable(OgException e);
inline OgBoolean OgExceptionIsNothing(OgException e);
OG_MACRO_EXTERN OgException OgExceptionCreateCallStack(
    OgPVoid *aFrames,
    OgUnsignedIntegerSize uMaxFrames);
OG_MACRO_EXTERN OgException OgExceptionThrowOutOfRangeV(
    OgConstString pcsParameter,
    OgConstString pcsMax,
    OgConstString pcsMin);
OG_MACRO_EXTERN OgException OgExceptionThrowOutOfRangeD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter,
    OgConstString pcsMax,
    OgConstString pcsMin);
inline OgConstString OgExceptionOutOfRangeGetExceptionTypeName();
OG_MACRO_EXTERN OgException OgExceptionIsOutOfRange(
    const OgException *e,
    OgBoolean *pbResult);
OG_MACRO_EXTERN OgException OgExceptionThrowInvalidArgumentV(OgConstString pcsParameter);
OG_MACRO_EXTERN OgException OgExceptionThrowInvalidArgumentD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter);
OG_MACRO_EXTERN OgException OgExceptionThrowArgumentNullV(OgConstString pcsParameter);
OG_MACRO_EXTERN OgException OgExceptionThrowArgumentNullD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter);
OG_MACRO_EXTERN OgException OgExceptionThrowInvalidOperationV(void);
OG_MACRO_EXTERN
OgException OgExceptionThrowInvalidOperationD(OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT);
OG_MACRO_EXTERN OgException OgExceptionThrowFormatExceptionV(OgConstString pcsFormatString);
OG_MACRO_EXTERN OgException OgExceptionThrowFormatExceptionD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsFormatSource);
OG_MACRO_EXTERN OgException OgExceptionThrowRuntimeExceptionV();
OG_MACRO_EXTERN
OgException OgExceptionThrowRuntimeExceptionD(OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT);
OG_MACRO_EXTERN OgException OgExceptionThrowOutOfMemoryV(void);
OG_MACRO_EXTERN
OgException OgExceptionThrowOutOfMemoryD(OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT);
OG_MACRO_EXTERN OgException OgExceptionThrowStackOverflowV(OgConstString pcsParameter);
OG_MACRO_EXTERN OgException OgExceptionThrowStackOverflowD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter);
#define OgExceptionThrowNothing() OgExceptionCreate(NULL, NULL)
#if !DEBUG
#define OgExceptionThrowLogicException OgExceptionThrowLogicExceptionV
#define OgExceptionThrowOutOfRange OgExceptionThrowOutOfRangeV
#define OgExceptionThrowInvalidArgument OgExceptionThrowInvalidArgumentV
#define OgExceptionThrowArgumentNull OgExceptionThrowArgumentNullV
#define OgExceptionThrowInvalidOperation OgExceptionThrowInvalidOperationV
#define OgExceptionThrowFormatException OgExceptionThrowFormatExceptionV
#define OgExceptionThrowRuntimeException OgExceptionThrowRuntimeExceptionV
#define OgExceptionThrowOutOfMemory OgExceptionThrowOutOfMemoryV
#define OgExceptionThrowStackOverflow OgExceptionThrowStackOverflowV
#else
#define OgExceptionThrowOutOfRange(...)                                                            \
    OgExceptionThrowOutOfRangeD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT, ##__VA_ARGS__)
#define OgExceptionThrowInvalidArgument(...)                                                       \
    OgExceptionThrowInvalidArgumentD(                                                              \
        OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT, ##__VA_ARGS__)
#define OgExceptionThrowArgumentNull(...)                                                          \
    OgExceptionThrowArgumentNullD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT, ##__VA_ARGS__)
#define OgExceptionThrowInvalidOperation()                                                         \
    OgExceptionThrowInvalidOperationD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT)
#define OgExceptionThrowFormatException(...)                                                       \
    OgExceptionThrowFormatExceptionD(                                                              \
        OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT, ##__VA_ARGS__)
#define OgExceptionThrowRuntimeException()                                                         \
    OgExceptionThrowRuntimeExceptionD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT)
#define OgExceptionThrowOutOfMemory()                                                              \
    OgExceptionThrowOutOfMemoryD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT)
#define OgExceptionThrowStackOverflow(...)                                                         \
    OgExceptionThrowStackOverflowD(OG_MACRO_THROW_EXCEPTION_EXTENSION_FILL_PARAMENT, ##__VA_ARGS__)

#endif

OG_MACRO_C_BLOCK_END
#include <OpenSTG/OpenStgBase.Exceptions.Inline.h>
#endif

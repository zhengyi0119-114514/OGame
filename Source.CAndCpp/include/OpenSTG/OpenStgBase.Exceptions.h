#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTIONS_H)
#define OPEN_STG_MACRO_BASE_EXCEPTIONS_H 1
#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H)
#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#endif
#define OgExceptionStructureOutOfRangeGetMaximumStringLength 32
#define OgExceptionStructureOutOfRangeGetMinimumStringLength 32
#define OgExceptionDebugInformationGetCallstackSize 32

OG_MACRO_C_BLOCK_BEGIN

typedef struct OgExceptionDebugInformation
{
    OgUnsignedInteger64 Line;
    OgConstantString File;
    OgConstantString Function;
    OgPVoid Callstack[OgExceptionDebugInformationGetCallstackSize];
} OgExceptionDebugInformation;

typedef struct OgExceptionStructureOutOfRange
{
    struct OgExceptionDebugInformation DebugInformation;
    struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgCharacter MaximumValue[OgExceptionStructureOutOfRangeGetMaximumStringLength];
    OgCharacter MinimumValue[OgExceptionStructureOutOfRangeGetMinimumStringLength];
    OgConstantString Description;
} OgExceptionStructureOutOfRange;

inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreateWithInteger64(
    OgConstantString pcsParamenter,
    OgSignedInteger64 iMaximumValue,
    OgSignedInteger64 iMinimumValue,
    OgConstantString pcsDescription
);
inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreate(
    OgConstantString pcsParamenter,
    OgConstantString pcsMaximumValue,
    OgConstantString pcsMinimumValue,
    OgConstantString pcsDescription
);
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(void);

typedef struct OgExceptionStructureInvalidArgument
{
    struct OgExceptionDebugInformation DebugInformation;
    struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgConstantString Description;
} OgExceptionStructureInvalidArgument;
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureInvalidArgumentGetInformation(
    void
);
inline struct OgExceptionStructureInvalidArgument OgExceptionStructureInvalidArgumentCreate(
    OgConstantString pcsParamenter, OgConstantString pcsDescription
);

typedef struct OgExceptionStructureUndefineBehavior
{
    struct OgExceptionInformation *Information;
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureUndefineBehavior;

inline struct OgExceptionStructureUndefineBehavior OgExceptionStructureUndefineBehaviorCreate(
    OgConstantString pcsDescription
);

OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureUndefineBehaviorGetInformation(
    void
);

typedef struct OgExceptionStructureFormatException
{
    struct OgExceptionDebugInformation DebugInformation;
    struct OgExceptionInformation *Information;
    OgConstantString Description;
} OgExceptionStructureFormatException;

typedef enum OgExceptionEnumMemoryExceptionType
{
    OgExceptionEnumMemoryExceptionTypeItemNone = 0,
    OgExceptionEnumMemoryExceptionTypeItemStackOverflow = 1,
    OgExceptionEnumMemoryExceptionTypeItemOutOfMemory = 2,
    OgExceptionEnumMemoryExceptionTypeItemHeapOverflow = 3,
} OgExceptionEnumMemoryExceptionType;

typedef struct OgExceptionStructureMemoryException
{
    struct OgExceptionDebugInformation DebugInformation;
    struct OgExceptionInformation *Information;
    OgUnsignedInteger64 ProcessId;
    OgUnsignedInteger64 ThreadId;
    enum OgExceptionEnumMemoryExceptionType Type;
} OgExceptionStructureMemoryException;

inline struct OgExceptionStructureMemoryException
    OgExceptionStructureMemoryExceptionCreateOutOfMemory();

typedef enum OgExceptionEnumFormattingExceptionType
{
    OgExceptionEnumFormatingExceptionItemNone = 0,
    OgExceptionEnumFormatingExceptionItemInvalidArgument = 1,
    OgExceptionEnumFormatingExceptionItemOutOfRange = 2,
    OgExceptionEnumFormatingExceptionItemUndefineBehavior = 3,
} OgExceptionEnumFormattingExceptionType;

typedef struct OgExceptionCollectionFormatException
{
    OgExceptionEnumFormattingExceptionType Type;
    union
    {
        OgExceptionStructureOutOfRange OutOfRange;
        OgExceptionStructureInvalidArgument InvalidArgument;
        OgExceptionStructureUndefineBehavior UndefineBehavior;
    };
} OgExceptionCollectionFormatException;

typedef enum OgExceptionEnumIoExceptionType
{
    OgExceptionEnumIoExceptionItemNone = 0,
    OgExceptionEnumIoExceptionItemInvalidArgument = 1,
    OgExceptionEnumIoExceptionItemUndefineBehavior = 2,
    OgExceptionEnumIoExceptionItemMemoryException = 3,
    OgExceptionEnumIoExceptionItemOutOfRange = 4,
} OgExceptionEnumIoExceptionType;

typedef struct OgExceptionCollectionIoException
{
    enum OgExceptionEnumIoExceptionType Type;
    union
    {
        struct OgExceptionStructureInvalidArgument InvalidArgument;
        struct OgExceptionStructureUndefineBehavior UndefineBehavior;
        struct OgExceptionStructureMemoryException MemoryException;
        struct OgExceptionStructureOutOfRange OutOfRange;
    };
} OgExceptionCollectionIoException;

typedef OgExceptionCollectionFormatException (*OgExceptionFunctionDefinitionFormatExceptionMessage)(
    OgPVoid pvExceptionSource,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgString psDestinationBuffer
);
typedef OgExceptionCollectionFormatException (*OgExceptionFunctionDefinitionGetExceptionMessageLength)(
    OgPVoid pvExceptionSource, OgUnsignedInteger64 *const puMessageLength
);
typedef OgExceptionCollectionFormatException (*OgExceptionFunctionDefinitionSerialize)(
    OgPVoid pvExceptionSource,
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize
);
typedef OgExceptionCollectionFormatException (*OgExceptionFunctionDefinitionDeserialize)(
    OgPVoid pvDestinationBuffer,
    OgUnsignedInteger64 puDestinationBufferSize,
    OgPVoid pvSourceBuffer,
    OgUnsignedInteger64 puSourceBufferSize
);
typedef OgConstantString (*OgExceptionFunctionDefinitionGetExceptionName)();

typedef struct OgExceptionInformation
{
    OgExceptionFunctionDefinitionFormatExceptionMessage FormatMessage;
    OgExceptionFunctionDefinitionGetExceptionMessageLength GetExceptionMessageLength;
    OgExceptionFunctionDefinitionSerialize Serialize;
    OgExceptionFunctionDefinitionDeserialize Deserialize;
    OgExceptionFunctionDefinitionGetExceptionName GetExceptionName;
} OgExceptionInformation;

OG_MACRO_MSVC_DECLSPEC(noreturn) OG_MACRO_NORETURN OG_MACRO_EXTERN void OgExceptionPanic(
    OgConstantString pcsDescription
) OG_MACRO_GNU_ATTRIBUTE(__noreturn__);

OG_MACRO_C_BLOCK_END

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H)
#include <OpenSTG/OpenStgBase.Exceptions.Inline.h>
#endif
#endif

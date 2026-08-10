#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTIONS_H)
#define OPEN_STG_MACRO_BASE_EXCEPTIONS_H 1
#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H)
#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#endif
#define OgExceptionStructureConstantOutOfRangeGetMaximumStringLength OgMacroSignedIntegerSizeConstant(32)
#define OgExceptionStructureConstantOutOfRangeGetMinimumStringLength OgMacroSignedIntegerSizeConstant(32)
#define OgExceptionConstantDebugInformationGetCallstackSize OgMacroSignedIntegerSizeConstant(32)

OgMacroCBlockBegin

typedef struct OgExceptionDebugInformation
{
    OgUnsignedInteger64 Line;
    OgConstantString File;
    OgConstantString Function;
    OgPVoid Callstack[OgExceptionConstantDebugInformationGetCallstackSize];
} OgExceptionDebugInformation;

typedef struct OgExceptionStructureOutOfRange
{
    struct OgExceptionDebugInformation DebugInformation;
    const struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgCharacter MaximumValue[OgExceptionStructureConstantOutOfRangeGetMaximumStringLength];
    OgCharacter MinimumValue[OgExceptionStructureConstantOutOfRangeGetMinimumStringLength];
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
OgMacroExtern const struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(
    void
);

typedef struct OgExceptionStructureInvalidArgument
{
    struct OgExceptionDebugInformation DebugInformation;
    const struct OgExceptionInformation *Information;
    OgConstantString Paramenter;
    OgConstantString Description;
} OgExceptionStructureInvalidArgument;
OgMacroExtern const struct OgExceptionInformation *
    OgExceptionStructureInvalidArgumentGetInformation(void);
inline struct OgExceptionStructureInvalidArgument OgExceptionStructureInvalidArgumentCreate(
    OgConstantString pcsParamenter,
    OgConstantString pcsDescription
);

typedef struct OgExceptionStructureUndefineBehavior
{
    const struct OgExceptionInformation *Information;
    OgConstantString Description;
    struct OgExceptionDebugInformation DebugInformation;
} OgExceptionStructureUndefineBehavior;

inline struct OgExceptionStructureUndefineBehavior OgExceptionStructureUndefineBehaviorCreate(
    OgConstantString pcsDescription
);

OgMacroExtern const struct OgExceptionInformation *
    OgExceptionStructureUndefineBehaviorGetInformation(void);

typedef struct OgExceptionStructureFormatException
{
    struct OgExceptionDebugInformation DebugInformation;
    const struct OgExceptionInformation *Information;
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
    const struct OgExceptionInformation *Information;
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

typedef struct OgExceptionInformation
{
    struct OgExceptionCollectionFormatException (*FormatMessage)(
        OgPVoid pvExceptionSource,
        OgUnsignedIntegerSize uDestinationBufferSize,
        OgString psDestinationBuffer
    );
    struct OgExceptionCollectionFormatException (*GetExceptionMessageLength)(
        OgPVoid pvExceptionSource,
        OgUnsignedIntegerSize *const puMessageLength
    );
    struct OgExceptionCollectionFormatException (*Serialize)(
        OgPVoid pvExceptionSource,
        OgPVoid pvDestinationBuffer,
        OgUnsignedIntegerSize puDestinationBufferSize
    );
    struct OgExceptionCollectionFormatException (*Deserialize)(
        OgPVoid pvDestinationBuffer,
        OgUnsignedIntegerSize puDestinationBufferSize,
        OgPVoid pvSourceBuffer,
        OgUnsignedIntegerSize puSourceBufferSize
    );
    OgConstantString (*GetExceptionName)(void);
} OgExceptionInformation;

OgMacroNoreturn OgMacroExtern void OgExceptionPanic(
    OgMacroMsvc(_In_opt_z_) OgConstantString pcsDescription
) OgMacroGnuAttribute(__noreturn__,__nothrow__);

OgMacroCBlockEnd

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H)
#include <OpenSTG/OpenStgBase.Exceptions.Inline.h>
#endif
#endif

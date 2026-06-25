#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H)
#define OPEN_STG_MACRO_BASE_EXCEPTION_STRUCTURES_H 1
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

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_H)
#include <OpenSTG/OpenStgBase.Exceptions.h>
#endif

OG_MACRO_C_BLOCK_END
#endif

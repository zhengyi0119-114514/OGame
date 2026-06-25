#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_INLINE_H)
#define OPEN_STG_MACRO_BASE_EXCEPTION_INLINE_H 1

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTIONS_H)
#include <OpenSTG/OpenStgBase.Exceptions.h>
#endif

OG_MACRO_C_BLOCK_BEGIN

inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreate(
    OgConstantString pcsParamenter,
    OgConstantString pcsMaximumValue,
    OgConstantString pcsMinimumValue,
    OgConstantString pcsDescription)
{
    OgExceptionStructureOutOfRange e = {};
    e.Information = OgExceptionStructureOutOfRangeGetInformation();
    e.Paramenter = pcsParamenter;
    e.Description = pcsDescription;
    strncpy(e.MaximumValue, pcsMaximumValue, sizeof(e.MaximumValue) - 1);
    strncpy(e.MinimumValue, pcsMinimumValue, sizeof(e.MinimumValue) - 1);
    return e;
}
inline OgExceptionStructureOutOfRange OgExceptionStructureOutOfRangeCreateWithInteger64(
    OgConstantString pcsParamenter,
    OgSignedInteger64 iMaximumValue,
    OgSignedInteger64 iMinimumValue,
    OgConstantString pcsDescription)
{

    OgExceptionStructureOutOfRange exception = {};
    exception.Information = OgExceptionStructureOutOfRangeGetInformation();
    exception.Paramenter = pcsParamenter;
    if (snprintf(exception.MaximumValue, sizeof(exception.MaximumValue), "%" PRIx64, iMaximumValue)
        < 0)
        OgExceptionPanic("Undefine Behavior.");
    if (snprintf(exception.MinimumValue, sizeof(exception.MinimumValue), "%" PRIx64, iMinimumValue)
        < 0)
        OgExceptionPanic("Undefine Behavior.");
    exception.Description = pcsDescription;
    return exception;
};
inline struct OgExceptionStructureInvalidArgument OgExceptionStructureInvalidArgumentCreate(
    OgConstantString pcsParamenter, OgConstantString pcsDescription);
inline struct OgExceptionStructureUndefineBehavior OgExceptionStructureUndefineBehaviorCreate(
    OgConstantString pcsDescription);
OG_MACRO_C_BLOCK_END
#endif

#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>

#if !defined(OPEN_STG_MACRO_BASE_EXCEPTION_H)
#define OPEN_STG_MACRO_BASE_EXCEPTION_H 1
OG_MACRO_C_BLOCK_BEGIN

inline OgException OgExceptionCreate(
    const struct OgExceptionInformation *peiInformation,
    OgPVoid pvAdditionalData)
{
    OgException e = {peiInformation, pvAdditionalData};
    return e;
}
inline OgBoolean OgExceptionExceptionIsNothing(OgException e)
{
    return e.AdditionalData == NULL;
}

inline OgBoolean OgExceptionSerializable(OgException e)
{
    return e.Information->ExceptionSerialization != NULL &&
           e.Information->ExceptionDeserialization != NULL;
}
OG_MACRO_ALWAYS_INLINE inline OgConstString OgExceptionOutOfRangeGetExceptionTypeName()
{
    return "OpenStg.Base.Exception.LogicException.OutOfRange";
}
OG_MACRO_C_BLOCK_END
#endif

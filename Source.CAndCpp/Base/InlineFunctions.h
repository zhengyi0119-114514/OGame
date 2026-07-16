#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_INLINE_FUNCTIONS_H)
#define OPEN_STG_INLINE_FUNCTIONS_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_ALWAYS_INLINE inline OgSignedInteger64 OgPrivateSignedInteger64Max(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OG_MACRO_ALWAYS_INLINE inline OgSignedInteger64 OgPrivateSignedInteger64Min(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}
OG_MACRO_ALWAYS_INLINE inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Max(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OG_MACRO_ALWAYS_INLINE inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Min(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}
OG_MACRO_ALWAYS_INLINE inline size_t OgPrivateSizeT64Max(
    size_t lsh, size_t rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OG_MACRO_ALWAYS_INLINE inline size_t OgPrivateSizeTMin(
    size_t lsh, size_t rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}
/// NOTE: 用来包装检查
OG_MACRO_ALWAYS_INLINE inline OgBoolean OgPrivatePVoidIsNull(
    OgPVoid ptr
)
{
    return ptr == NULL;
}
#define OgPrivateIsNull(ptr) OgPrivatePVoidIsNull((OgPVoid)(ptr))
OG_MACRO_C_BLOCK_END
#endif

#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_INLINE_FUNCTIONS_H)
#define OPEN_STG_INLINE_FUNCTIONS_H 1
OG_MACRO_C_BLOCK_BEGIN

inline OgSignedInteger64 OgPrivateSignedInteger64Max(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh)
{
    return (lsh <= rsh) ? rsh : lsh;
}
inline OgSignedInteger64 OgPrivateSignedInteger64Min(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh)
{
    return (lsh >= rsh) ? rsh : lsh;
}
inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Max(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh)
{
    return (lsh <= rsh) ? rsh : lsh;
}
inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Min(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh)
{
    return (lsh >= rsh) ? rsh : lsh;
}
inline size_t OgPrivateSizeT64Max(
    size_t lsh, size_t rsh)
{
    return (lsh <= rsh) ? rsh : lsh;
}
inline size_t OgPrivateSizeTMin(
    size_t lsh, size_t rsh)
{
    return (lsh >= rsh) ? rsh : lsh;
}
OG_MACRO_C_BLOCK_END
#endif

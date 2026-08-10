#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>

#if !defined(OPEN_STG_INLINE_FUNCTIONS_H)
#define OPEN_STG_INLINE_FUNCTIONS_H 1
OgMacroCBlockBegin

OgMacroAlwaysInline inline OgSignedInteger64 OgPrivateSignedInteger64Max(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OgMacroAlwaysInline inline OgSignedInteger64 OgPrivateSignedInteger64Min(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}
OgMacroAlwaysInline inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Max(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OgMacroAlwaysInline inline OgUnsignedInteger64 OgPrivateUnsignedInteger64Min(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}

OgMacroAlwaysInline inline size_t OgPrivateSizeTMax(
    size_t lsh, size_t rsh
)
{
    return (lsh <= rsh) ? rsh : lsh;
}
OgMacroAlwaysInline inline size_t OgPrivateSizeTMin(
    size_t lsh, size_t rsh
)
{
    return (lsh >= rsh) ? rsh : lsh;
}

OgMacroAlwaysInline inline OgBoolean OgPrivatePVoidIsNull(
    OgPVoid ptr
)
{
    return ptr == NULL;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSizeTEqual(
    size_t lsh, size_t rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSSizeTEqual(
    ssize_t lsh, ssize_t rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivatePointerSizedUnsignedIntegerEqual(
    OgPointerSizedUnsignedInteger lsh, OgPointerSizedUnsignedInteger rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivatePointerSizedSignedIntegerEqual(
    OgPointerSizedSignedInteger lsh, OgPointerSizedSignedInteger rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSignedInteger64Equal(
    OgSignedInteger64 lsh, OgSignedInteger64 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateUnsignedInteger64Equal(
    OgUnsignedInteger64 lsh, OgUnsignedInteger64 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSignedInteger32Equal(
    OgSignedInteger32 lsh, OgSignedInteger32 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateUnsignedInteger32Equal(
    OgUnsignedInteger32 lsh, OgUnsignedInteger32 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSignedInteger16Equal(
    OgSignedInteger16 lsh, OgSignedInteger16 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateUnsignedInteger16Equal(
    OgUnsignedInteger16 lsh, OgUnsignedInteger16 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateSignedInteger8Equal(
    OgSignedInteger8 lsh, OgSignedInteger8 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateUnsignedInteger8Equal(
    OgUnsignedInteger8 lsh, OgUnsignedInteger8 rsh
)
{
    return lsh == rsh;
}
OgMacroAlwaysInline inline OgBoolean OgPrivateStringEqual(
    OgConstantString const lsh, OgConstantString const rsh
)
{
    return strcmp(lsh, rsh) == 0;
}

#define OgPrivateIsNull(ptr) OgPrivatePVoidIsNull(OgMacroStaticCast(OgPVoid,ptr))
OgMacroCBlockEnd
#endif

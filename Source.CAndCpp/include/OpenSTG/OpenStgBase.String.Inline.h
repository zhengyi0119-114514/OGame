#include <OpenSTG/OpenStgBase.String.h>
#include <OpenSTG/OpenStgBase.Memory.h>

#if !defined OPEN_STG_MACRO_BASE_STRING_INLINE_H
#define OPEN_STG_MACRO_BASE_STRING_INLINE_H
OG_MACRO_C_BLOCK_BEGIN

inline OgString OgStringAllocMemoryAndInitialize(
    OgUnsignedIntegerSize uLength)
{
    OgAllocator a = OgAllocatorCreateCStandardAllocator();
    OgString psString = a.Alloc(&a, uLength);
    if (psString != NULL)
    {
        memset((OgPVoid)psString, 0, uLength);
    }
    return psString;
}
inline void OgStringFree(
    OgString psString)
{
    OgAllocator a = OgAllocatorCreateCStandardAllocator();
    a.Free(&a, (OgPVoid)psString);
}
inline OgString OgStringAllocMemoryAndClone(
    OgConstString pcsSource)
{
    OgAllocator a = OgAllocatorCreateCStandardAllocator();
    OgUnsignedIntegerSize uNewStringLength = strlen(pcsSource) + 1;
    OgString psNewString = a.Alloc(&a, uNewStringLength);
    if (psNewString != NULL)
    {
        memset((OgPVoid)psNewString, 0, uNewStringLength);
    }
    return psNewString;
}

OG_MACRO_C_BLOCK_END
#endif

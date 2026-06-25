#include "Allocator.h"

OG_MACRO_PRIVATE OgPVoid OgPvStdAllocWarp(
    struct OgAllocator *pAllocator,
    OgUnsignedIntegerSize uSize)
{
    OgPVoid pvMemory = malloc(uSize);
    return pvMemory;
}
OG_MACRO_PRIVATE OgPVoid OgPvStdAlignedAllocWarp(
    struct OgAllocator *pAllocator,
    OgUnsignedIntegerSize uMemorySize,
    OgUnsignedIntegerSize uAligned)
{
#if defined(_WIN32)
    OgPVoid pvMemory = _aligned_malloc(uMemorySize, uAligned);
#else
    OgPVoid pvMemory = aligned_alloc(uAligned, uMemorySize);
#endif
    if (pvMemory != NULL)
    {
        memset(pvMemory, 0, uMemorySize);
    }
    return pvMemory;
}
OG_MACRO_PRIVATE OgPVoid OgPvStdReallocWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize)
{
    if (uNewSize == 0)
    {
        free(pvOld);
        return NULL;
    }
    return realloc(pvOld, uNewSize);
}
OG_MACRO_PRIVATE void OgPvStdFreeWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pv)
{
    free(pv);
}
OG_MACRO_PRIVATE void OgPvStdAlignedFreeWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pv)
{
#if defined(_WIN32)
    _aligned_free(pv)
#else
    free(pv);
#endif
}
OgAllocator OgAllocatorCreateCStandardAllocator()
{
    const OgAllocator a = {
        OgPvStdAllocWarp,
        OgPvStdReallocWarp,
        OgPvStdFreeWarp,
        OgPvStdAlignedAllocWarp,
        OgPvStdAlignedFreeWarp,
        NULL,
        NULL
    };
    return a;
}

#include "Allocator.h"

OgPVoid OgPrivateStandardAllocWarp(
    struct OgAllocator *pAllocator, OgUnsignedIntegerSize uSize)
{
    OgPVoid pvMemory = malloc(uSize);
    return pvMemory;
}
OgPVoid OgPrivateStandardAlignedAllocWarp(
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
OgPVoid OgPrivateStandardReallocWarp(
    struct OgAllocator *pAllocator, OgPVoid pvOld, OgUnsignedIntegerSize uNewSize)
{
    if (uNewSize == 0)
    {
        free(pvOld);
        return NULL;
    }
    return realloc(pvOld, uNewSize);
}
void OgPrivateStandardFreeWarp(
    struct OgAllocator *pAllocator, OgPVoid pv)
{
    free(pv);
}
void OgPrivateStandardAlignedFreeWarp(
    struct OgAllocator *pAllocator, OgPVoid pv)
{
#if defined(_WIN32)
    _aligned_free(pv)
#else
    free(pv);
#endif
}
OgAllocator OgMemoryAllocatorCreateCStandardAllocator()
{
    const OgAllocator a
        = {OgPrivateStandardAllocWarp,
           OgPrivateStandardReallocWarp,
           OgPrivateStandardFreeWarp,
           OgPrivateStandardAlignedAllocWarp,
           OgPrivateStandardAlignedFreeWarp,
           NULL,
           NULL};
    return a;
}

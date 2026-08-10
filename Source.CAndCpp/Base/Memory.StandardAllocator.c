#include "Memory.h"

OgPVoid OgPrivateStandardAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uSize
)
{
    OgPVoid pvMemory = malloc(uSize);
    return pvMemory;
}
OgPVoid OgPrivateStandardAlignedAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uMemorySize,
    OgUnsignedIntegerSize uAligned
)
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
    struct OgAllocator *paAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize
)
{
    if (uNewSize == 0)
    {
        free(pvOld);
        return NULL;
    }
    return realloc(pvOld, uNewSize);
}
void OgPrivateStandardFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv
)
{
    free(pv);
}
void OgPrivateStandardAlignedFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv
)
{
#if defined(_WIN32)
    _aligned_free(pv)
#else
    free(pv);
#endif
}
static struct OgAllocator s_aStandardAllocator = {
    OgPrivateStandardAllocWarp,
    OgPrivateStandardReallocWarp,
    OgPrivateStandardFreeWarp,
    OgPrivateStandardAlignedAllocWarp,
    OgPrivateStandardAlignedFreeWarp,
    OgPrivateStandardDestroy,
    NULL};
struct OgAllocator *OgMemoryAllocatorCreateCStandardAllocator()
{
    return &s_aStandardAllocator;
}
void OgPrivateStandardDestroy(
    struct OgAllocator *paAllocator
)
{
}

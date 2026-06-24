#include "Allocator.h"

OgException OgAllocatorCheckBasic(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult)
{
    if (pAllocator == NULL)
    {
        return OgExceptionThrowArgumentNull("pAllocator");
    }
    *pbResult = pAllocator->Alloc != NULL && pAllocator->Free != NULL;
    return OgExceptionThrowNothing();
}
OgException OgAllocatorCheckSupportForAlignmentSupport(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult)
{
    if (pAllocator == NULL)
    {
        return OgExceptionThrowArgumentNull("pAllocator");
    }
    *pbResult = pAllocator->AlignedAlloc != NULL && pAllocator->AlignedFree != NULL;
    return OgExceptionThrowNothing();
}
OgException OgAllocatorCheckSupportForResize(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult)
{
    OgException e = OgExceptionThrowNothing();
    if (pAllocator == NULL)
    {
        return OgExceptionThrowArgumentNull("pAllocator");
    }
    OgBoolean bBaseCheckResult = OgFalse;
    OgExceptionDestroy(e);
    e = OgAllocatorCheckBasic(pAllocator, &bBaseCheckResult);
    if (!OgExceptionIsNothing(e))
    {
        return e;
    }
    *pbResult = bBaseCheckResult && (pAllocator->Realloc != NULL);
    return OgExceptionThrowNothing();
}
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
    OgAllocator a = {};
    memset((OgPVoid)&a, 0, sizeof(OgAllocator));
    a.Alloc = OgPvStdAllocWarp;
    a.Free = OgPvStdFreeWarp;
    a.Realloc = OgPvStdReallocWarp;
    a.AlignedAlloc = OgPvStdAlignedAllocWarp;
    return a;
}

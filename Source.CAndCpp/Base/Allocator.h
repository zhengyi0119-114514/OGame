#include <OpenSTG/OpenStgBase.h>

#if !defined(OPEN_STG_ALLOCATOR_H)
#define OPEN_STG_ALLOCATOR_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardAllocWarp(
    struct OgAllocator *pAllocator,
    OgUnsignedIntegerSize uSize);

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardAlignedAllocWarp(
    struct OgAllocator *pAllocator,
    OgUnsignedIntegerSize uMemorySize,
    OgUnsignedIntegerSize uAligned);

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardReallocWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize);

OG_MACRO_PRIVATE void OgPrivateStandardFreeWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pv);

OG_MACRO_PRIVATE void OgPrivateStandardAlignedFreeWarp(
    struct OgAllocator *pAllocator,
    OgPVoid pv);
OG_MACRO_C_BLOCK_END
#endif

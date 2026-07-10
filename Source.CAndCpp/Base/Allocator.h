#include <OpenSTG/OpenStgBase.h>

#if !defined(OPEN_STG_ALLOCATOR_H)
#define OPEN_STG_ALLOCATOR_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uSize);

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardAlignedAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uMemorySize,
    OgUnsignedIntegerSize uAligned);

OG_MACRO_PRIVATE OgPVoid OgPrivateStandardReallocWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize);

OG_MACRO_PRIVATE void OgPrivateStandardFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv);

OG_MACRO_PRIVATE void OgPrivateStandardAlignedFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv);
OG_MACRO_C_BLOCK_END
#endif

#include <OpenSTG/OpenStgBase.h>
#if !defined(OPEN_STG_ALLOCATOR_H)
#define OPEN_STG_ALLOCATOR_H 1
OgMacroCBlockBegin

OgMacroPrivate OgPVoid OgPrivateStandardAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uSize
);

OgMacroPrivate OgPVoid OgPrivateStandardAlignedAllocWarp(
    struct OgAllocator *paAllocator,
    OgUnsignedIntegerSize uMemorySize,
    OgUnsignedIntegerSize uAligned
);

OgMacroPrivate OgPVoid OgPrivateStandardReallocWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize
);

OgMacroPrivate void OgPrivateStandardFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv
);

OgMacroPrivate void OgPrivateStandardAlignedFreeWarp(
    struct OgAllocator *paAllocator,
    OgPVoid pv
);
OgMacroPrivate void OgPrivateStandardDestroy(struct OgAllocator *paAllocator);
OgMacroExport struct OgAllocator *OgMemoryAllocatorCreateCStandardAllocator();
OgMacroExport struct OgAllocator *OgMemoryAllocatorGetDefaultAllocator();

OgMacroCBlockEnd
#endif

#include <OpenSTG/OpenStgBase.Types.h>

#if !defined(OPEN_STG_MACRO_BASE_MEMNRY_H)
#define OPEN_STG_MACRO_BASE_MEMNRY_H 1

#include <OpenSTG/OpenStgBase.Exceptions.h>

OgMacroCBlockBegin

typedef struct OgAllocator
{
    OgPVoid (*Alloc)(
        struct OgAllocator *paAllocator,
        OgUnsignedIntegerSize uSize
    );
    OgPVoid (*Realloc)(
        struct OgAllocator *paAllocator,
        OgPVoid pvOld,
        OgUnsignedIntegerSize uNewSize
    );
    void (*Free)(
        struct OgAllocator *paAllocator,
        OgPVoid pMemory
    );
    OgPVoid (*AlignedAlloc)(
        struct OgAllocator *paAllocator,
        OgUnsignedIntegerSize uSize,
        OgUnsignedIntegerSize uAlignment
    );
    void (*AlignedFree)(
        struct OgAllocator *paAllocator,
        OgPVoid pMemory
    );
    void (*Destroy)(struct OgAllocator *paAllocator);
    OgPVoid AdditionalData;
} OgAllocator;

OgMacroExtern struct OgAllocator *OgMemoryAllocatorCreateCStandardAllocator();
OgMacroExtern struct OgAllocator *OgMemoryAllocatorGetDefaultAllocator();

OgMacroCBlockEnd
#endif

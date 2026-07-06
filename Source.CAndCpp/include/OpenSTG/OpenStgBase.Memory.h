#include <OpenSTG/OpenStgBase.Types.h>

#if !defined(OPEN_STG_MACRO_BASE_MEMNRY_H)
#define OPEN_STG_MACRO_BASE_MEMNRY_H 1

#include <OpenSTG/OpenStgBase.Exceptions.h>

OG_MACRO_C_BLOCK_BEGIN

typedef struct OgAllocator
{
    OgPVoid (*Alloc)(struct OgAllocator *pAllocator, OgUnsignedIntegerSize uSize);
    OgPVoid (*Realloc)(
        struct OgAllocator *pAllocator, OgPVoid pvOld, OgUnsignedIntegerSize uNewSize);
    void (*Free)(struct OgAllocator *pAllocator, OgPVoid pMemory);
    OgPVoid (*AlignedAlloc)(
        struct OgAllocator *pAllocator,
        OgUnsignedIntegerSize uSize,
        OgUnsignedIntegerSize uAlignment);
    void (*AlignedFree)(struct OgAllocator *pAllocator, OgPVoid pMemory);
    void (*Destroy)(struct OgAllocator *pAllocator);
    OgPVoid AdditionalData;
} OgAllocator;
OG_MACRO_EXTERN struct OgAllocator OgMemoryAllocatorCreateCStandardAllocator();
OG_MACRO_EXTERN struct OgAllocator *OgMemoryAllocatorGetDefaultAllocator();

OG_MACRO_C_BLOCK_END
#endif

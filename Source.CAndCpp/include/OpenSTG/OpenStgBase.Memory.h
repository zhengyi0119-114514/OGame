#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>

#if !defined(OPEN_STG_MACRO_BASE_MEMNRY)
#define OPEN_STG_MACRO_BASE_MEMNRY 1
OG_MACRO_C_BLOCK_BEGIN

typedef OgPVoid (*OgMemoryFunctionDefinitionAlloc)(
    struct OgAllocator *pAllocator, OgUnsignedIntegerSize uSize);
typedef OgPVoid (*OgMemoryFunctionDefinitionAlignedAlloc)(
    struct OgAllocator *pAllocator,
    OgUnsignedIntegerSize uSize,
    OgUnsignedIntegerSize uAlignment);
typedef OgPVoid (*OgMemoryFunctionDefinitionRealloc)(
    struct OgAllocator *pAllocator,
    OgPVoid pvOld,
    OgUnsignedIntegerSize uNewSize);
typedef void (*OgMemoryFunctionDefinitionFree)(
    struct OgAllocator *pAllocator, OgPVoid pMemory);
typedef void (*OgMemoryFunctionDefinitionAlignedFree)(
    struct OgAllocator *pAllocator, OgPVoid pMemory);
typedef void (*OgMemoryFunctionDefinitionAllocatorDestroy)(
    struct OgAllocator *pAllocator);
typedef struct OgAllocator
{
    OgMemoryFunctionDefinitionAlloc Alloc;
    OgMemoryFunctionDefinitionRealloc Realloc;
    OgMemoryFunctionDefinitionFree Free;
    OgMemoryFunctionDefinitionAlignedAlloc AlignedAlloc;
    OgMemoryFunctionDefinitionAlignedFree AlignedFree;
    OgMemoryFunctionDefinitionAllocatorDestroy Destroy;
    OgPVoid AdditionalData;
} OgAllocator;
OG_MACRO_EXTERN OgAllocator OgAllocatorCreateCStandardAllocator();
OG_MACRO_EXTERN struct OgAllocator *OgAllocatorGetDefaultAllocator();

OG_MACRO_C_BLOCK_END
#endif

#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>

#if !defined(OPEN_STG_MACRO_BASE_MEMNRY)
#define OPEN_STG_MACRO_BASE_MEMNRY 1
OG_MACRO_C_BLOCK_BEGIN

typedef struct OgAllocator
{
    OgPVoid (*Alloc)(
        struct OgAllocator *pAllocator,
        OgUnsignedIntegerSize uSize);
    OgPVoid (*AlignedAlloc)(
        struct OgAllocator *pAllocator,
        OgUnsignedIntegerSize uSize,
        OgUnsignedIntegerSize uAlignment);
    OgPVoid (*Realloc)(
        struct OgAllocator *pAllocator,
        OgPVoid pvOld,
        OgUnsignedIntegerSize uNewSize);
    void (*Free)(
        struct OgAllocator *pAllocator,
        OgPVoid pMemory);
    void (*AlignedFree)(
        struct OgAllocator *pAllocator,
        OgPVoid pMemory);
    OgPVoid AdditionalData;
    void (*DestroyAllocator)(
        struct OgAllocator *pAllocator,
        const struct OgAllocator *pMemory);
} OgAllocator;
OG_MACRO_EXTERN OgAllocator OgAllocatorCreateCStandardAllocator();
OG_MACRO_EXTERN struct OgAllocator* OgAllocatorGetDefaultAllocator();
OG_MACRO_EXTERN OgException OgAllocatorCheckBasic(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);
OG_MACRO_EXTERN OgException OgAllocatorCheckSupportForAlignmentSupport(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);
OG_MACRO_EXTERN OgException OgAllocatorCheckSupportForResize(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);

typedef struct OgDynamicArray
{
    OgUnsignedByte *Array;
    struct OgAllocator *Allocator;
    void (*DestroyItem)(OgPVoid pvItem);
    OgUnsignedIntegerSize Length;
    OgUnsignedIntegerSize UnitSize;
} OgDynamicArray;

OG_MACRO_EXTERN OgException OgDynamicArrayCreate(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uUnitSize,
    OgUnsignedIntegerSize uLength,
    OgSignedInteger64 uAlign,
    struct OgAllocator *pAllocator,
    void (*DestroyItem)(OgPVoid pvItem));
OG_MACRO_EXTERN OgException OgDynamicArrayRemoveItem(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uIndex);
OG_MACRO_EXTERN OgException OgDynamicArrayAppendItem(
    OgDynamicArray *pArray,
    OgPVoid *pvItem);
OG_MACRO_EXTERN OgException OgDynamicArrayGetLength(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize *puSize);
OG_MACRO_EXTERN OgException OgDynamicArrayDestroy(OgDynamicArray *pArray);
OG_MACRO_EXTERN OgException OgDynamicArrayGetFront(
    OgDynamicArray *pArray,
    OgPVoid *ppvItem);
OG_MACRO_EXTERN OgException OgDynamicArrayGetBack(
    OgDynamicArray *pArray,
    OgPVoid *ppvItem);
OG_MACRO_EXTERN OgException OgDynamicArrayGetItem(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uIndex,
    OgPVoid *ppvItem);
OG_MACRO_EXTERN OgException OgDynamicArrayIsEmpty(
    OgDynamicArray *pArray,
    OgBoolean *pbResult);
OG_MACRO_EXTERN OgException OgDynamicArrayIsResizable(
    OgDynamicArray *pArray,
    OgBoolean *pbResult);
OG_MACRO_EXTERN OgException OgDynamicArrayClear(OgDynamicArray *pArray);

OG_MACRO_C_BLOCK_END
#endif

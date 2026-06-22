#include <OpenSTG/OpenStgBase.h>

#if !defined(OPEN_STG_ARRAY_H)
#define OPEN_STG_ARRAY_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_EXPORT OgException OgDynamicArrayCreate(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uUnitSize,
    OgUnsignedIntegerSize uLength,
    OgSignedInteger64 sAlign,
    struct OgAllocator *pAllocator,
    void (*DestroyItem)(OgPVoid pvItem));
OG_MACRO_EXPORT OgException OgDynamicArrayRemoveItem(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uIndex);
OG_MACRO_EXPORT OgException OgDynamicArrayAppendItem(
    OgDynamicArray *pArray,
    OgPVoid *pvItem);
OG_MACRO_EXPORT OgException OgDynamicArrayGetLength(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize *puSize);
OG_MACRO_EXPORT OgException OgDynamicArrayDestroy(OgDynamicArray *pArray);
OG_MACRO_EXPORT OgException OgDynamicArrayGetFront(
    OgDynamicArray *pArray,
    OgPVoid *pvItem);
OG_MACRO_EXPORT OgException OgDynamicArrayGetBack(
    OgDynamicArray *pArray,
    OgPVoid *pvItem);
OG_MACRO_EXPORT OgException OgDynamicArrayGetItem(
    OgDynamicArray *pArray,
    OgUnsignedIntegerSize uIndex,
    OgPVoid *ppvItem);
OG_MACRO_EXPORT OgException OgDynamicArrayIsEmpty(
    OgDynamicArray *pArray,
    OgBoolean *pbResult);
OG_MACRO_EXPORT OgException OgDynamicArrayIsResizable(
    OgDynamicArray *pArray,
    OgBoolean *pbResult);
OG_MACRO_EXPORT OgException OgDynamicArrayClear(OgDynamicArray *pArray);

OG_MACRO_C_BLOCK_END
#endif

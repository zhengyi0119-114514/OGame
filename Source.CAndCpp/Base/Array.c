#include "Array.h"
#include "Exception.h"
#include "StaticVariable.h"
#include <OpenSTG/OpenStgBase.h>
#include <stdlib.h>

OgException OgDynamicArrayCreate(OgDynamicArray *pArray,
    OgUnsignedIntegerSize uUnitSize,
    OgUnsignedIntegerSize uLength,
    OgSignedInteger64 sAlign,
    struct OgAllocator *pAllocator,
    void (*DestroyItem)(OgPVoid pvItem))
{
    OgBoolean bAllocatorAvailable = false;
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    if (pAllocator == NULL)
    {
        return OgExceptionThrowArgumentNull("pAllocator");
    }
    if (!OgExceptionExceptionIsNothing(OgAllocatorCheckBasic(pAllocator, &bAllocatorAvailable)))
    {
        return OgExceptionThrowInvalidArgument("pAllocator");
    }
    memset((OgPVoid)pArray, 0, sizeof(OgDynamicArray));
    pArray->Array = (OgByte *)calloc(uLength, uUnitSize);
    if (pArray->Array == NULL)
    {
        return OgExceptionThrowOutOfMemory();
    }
    pArray->Allocator = pAllocator;
    pArray->Length = uLength;
    pArray->DestroyItem = DestroyItem;
    pArray->UnitSize = uUnitSize;
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayRemoveItem(OgDynamicArray *pArray, OgUnsignedIntegerSize uIndex);
OgException OgDynamicArrayAppendItem(OgDynamicArray *pArray, OgPVoid *pvItem);
OgException OgDynamicArrayGetLength(OgDynamicArray *pArray, OgUnsignedIntegerSize *puSize)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    *puSize = pArray->Length;
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayDestroy(OgDynamicArray *pArray)
{
    if (pArray == NULL || pArray->DestroyItem == NULL)
    {
        return OgExceptionThrowNothing();
    }
    for (OgUnsignedIntegerSize uSize = 0; uSize < pArray->Length; uSize++)
    {
        pArray->DestroyItem((OgPVoid)(pArray->Array + uSize * pArray->UnitSize));
    }
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayGetFront(OgDynamicArray *pArray, OgPVoid *ppvItem)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    if (pArray->Length == 0)
    {
        return OgExceptionThrowInvalidOperation();
    }
    *ppvItem = (OgPVoid)(pArray->Array);
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayGetBack(OgDynamicArray *pArray, OgPVoid *ppvItem)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    if (ppvItem == NULL)
    {
        return OgExceptionThrowArgumentNull("ppvItem");
    }
    if (pArray->Length)
    {
        return OgExceptionThrowInvalidOperation();
    }
    *ppvItem = (OgPVoid)(pArray + pArray->UnitSize * (pArray->Length -1));
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayGetItem(OgDynamicArray *pArray,OgUnsignedIntegerSize uIndex,OgPVoid* ppvItem)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    if (ppvItem == NULL)
    {
        return OgExceptionThrowArgumentNull("ppvItem");
    }
    if (uIndex >= pArray->Length)
    {
        return OgExceptionThrowOutOfRange("uIndex",OgStringGetEmptyString(),OgStringGetEmptyString());
    }
    *ppvItem = (OgPVoid)(pArray->Array+pArray->UnitSize*uIndex);
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayIsEmpty(OgDynamicArray *pArray, OgBoolean *pbResult)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    *pbResult = pArray->Length == 0;
    return OgExceptionThrowNothing();
}
OgException OgDynamicArrayIsResizable(OgDynamicArray *pArray, OgBoolean *pbResult)
{
    if (pArray == NULL)
    {
        return OgExceptionThrowArgumentNull("pArray");
    }
    if (pbResult == NULL)
    {
        return OgExceptionThrowArgumentNull("pbResult");
    }
    return OgAllocatorCheckSupportForResize(pArray->Allocator, pbResult);
}
OgException OgDynamicArrayClear(OgDynamicArray *pArray);

#include "OpenStg/CloseStgCore.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct TagOgCrUNIVERSAL_REGISTRAR
{
    OG_CR_UNIVERSAL_REGISTRAR_FLAG_T ufRegistrarFlag;
    void *rgItems;
    BOOL_T *rgStatus;
    OG_CR_DESTORY_MEMBER_FUNCTION_T pfDestoryMemberFunction;
    uint64_t uUnitStructureSize;
    uint64_t uReservedItemCount; ///< rgItems和rgStatus的项数
} OG_CR_UNIVERSAL_REGISTRAR;

OG_CR_UNIVERSAL_REGISTRAR *OG_API OgCrCreateUniversalRegistrar(const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri)
{
    if (puri == NULL || (puri->uUnitStructureSize == 0 || puri->uSize < sizeof(OG_CR_UNIVERSAL_REGISTRAR)))
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return NULL;
    }
    if (puri->uPreAllocatedCount > OPEN_STG_CONST_MAX_STRUCTURE_COUNT ||
        puri->uUnitStructureSize > OPEN_STG_CONST_MAX_UNIT_STRUCTURE_SIZE)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE));
        return (NULL);
    }
    OG_CR_UNIVERSAL_REGISTRAR *pur = (OG_CR_UNIVERSAL_REGISTRAR *)malloc(sizeof(OG_CR_UNIVERSAL_REGISTRAR));
    uint64_t uPreAllocatedCount = puri->uPreAllocatedCount, uUnitStructureSize = puri->uUnitStructureSize;
    // 手动对齐void *
    if ((uUnitStructureSize % sizeof(void *)) != 0)
    {
        if (sizeof(void *) == 4 || sizeof(void *) == 8 || sizeof(void *) == 16)
        {
            uUnitStructureSize &= ~(uint64_t)sizeof(void *) + 1;
        }
        else // 什么，你的神人计算机的指针长度是6字节？
        {
            uUnitStructureSize -= uUnitStructureSize % sizeof(void *);
        }
        uUnitStructureSize += sizeof(void *);
    }
    void *rgItems = calloc(uPreAllocatedCount, uUnitStructureSize);
    BOOL_T *rgStatus = (BOOL_T *)calloc(uPreAllocatedCount, sizeof(BOOL_T));
    if (pur == NULL || rgItems == NULL || rgStatus == NULL)
    {
        free(rgItems);
        free((void *)rgStatus);
        free((void *)pur);
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return NULL;
    }
    if (OPEN_STG_MACRO_IS_DEBUG)
    {
        memset((void *)pur, 0, sizeof(OG_CR_UNIVERSAL_REGISTRAR));
        memset(rgItems, 0x2B, uPreAllocatedCount * uUnitStructureSize); //看看内存，有人在骂你2B
        memset((void *)rgStatus, 0, uPreAllocatedCount);
    }
    pur->rgItems = rgItems;
    pur->rgStatus = rgStatus;
    pur->uUnitStructureSize = uUnitStructureSize;
    pur->uReservedItemCount = uPreAllocatedCount;
    pur->pfDestoryMemberFunction = puri->pfDestoryMember;
    return (pur);
}
BOOL_T OG_API OgCrUniversalRegistrarReserveItems(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uReserveCount)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return (FALSE);
    }
    if ((pur->uReservedItemCount + uReserveCount) > OPEN_STG_CONST_MAX_STRUCTURE_COUNT)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE));
        return (NULL);
    }
    uint32_t uNewReserveCount = pur->uReservedItemCount + uReserveCount, uUnitStructureSize = pur->uUnitStructureSize;
    void *rgNewItems = NULL;
    if ((rgNewItems = realloc((void *)pur->rgItems, uNewReserveCount * uUnitStructureSize)) == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return (FALSE);
    }
    BOOL_T *rgNewStatus = NULL;
    if ((rgNewStatus = (BOOL_T *)realloc((void *)pur->rgStatus, uNewReserveCount * sizeof(BOOL_T))) == NULL)
    {
        pur->rgItems = realloc((void *)pur->rgItems, pur->uReservedItemCount * uUnitStructureSize);
        if (pur->rgItems == NULL)
        {
            // NOTE:一般不会运行到这里，如果运行到这里，这意味者系统的内存管理出现了错误，或者是这段代码的逻辑出现严重错误
            OgCrSetIrreversibleError(
                OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_UNDEFINED_MEMORY_ERROR));
            return (FALSE);
        }
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return (FALSE);
    }
    if ((pur->ufRegistrarFlag & 1) == 0)
    {
        void *pNewMomery = (BYTE_T *)rgNewItems + uUnitStructureSize * pur->uReservedItemCount;
        memset((void *)pNewMomery, 0x3B, uReserveCount * uUnitStructureSize);
    }
    memset(rgNewStatus + pur->uReservedItemCount * sizeof(BOOL_T), 0, uReserveCount * sizeof(BOOL_T));
    pur->rgItems = rgNewItems;
    pur->rgStatus = rgNewStatus;
    pur->uReservedItemCount = uNewReserveCount;
    return (TRUE);
}
int64_t OG_API OgCrUniversalRegistrarGetReservedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return -1;
    }
    return pur->uReservedItemCount;
}
int64_t OG_API OgCrUniversalRegistrarGetAllocatedItemCount(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return -1;
    }
    uint64_t uCount = 0;
    for (uint64_t uIndex = 0, uMax = pur->uReservedItemCount; uIndex < uMax; uIndex++)
    {
        if (pur->rgStatus[uIndex])
        {
            uCount++;
        }
    }
    return uCount;
}
void OG_API OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        return;
    }
    BOOL_T bContinue = TRUE;
    for (uint64_t uIndex = 0; bContinue && uIndex < pur->uReservedItemCount; uIndex++)
    {
        bContinue &= OgCrUniversalRegistrarFreeItem(pur, uIndex);
    }
    free(pur->rgItems);
    free(pur->rgStatus);
}
int64_t OG_API OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur, void **pOutput)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return (-1);
    }
    for (uint64_t uIndex = 0; uIndex < pur->uReservedItemCount; uIndex++)
    {
        if (!pur->rgStatus[uIndex])
        {
            pur->rgStatus[uIndex] = TRUE;
            if (pOutput != NULL)
            {
                (*pOutput) = (BYTE_T *)pur->rgItems + uIndex * pur->uUnitStructureSize;
            }
            return uIndex;
        }
    }
    uint32_t uNextIndex = pur->uReservedItemCount;
    if (!OgCrUniversalRegistrarReserveItems(pur, 1))
    {
        return (-1);
    }
    pur->rgStatus[uNextIndex] = TRUE;
    if (pOutput != NULL)
    {
        (*pOutput) = (BYTE_T *)pur->rgItems + uNextIndex * pur->uUnitStructureSize;
    }
    return uNextIndex;
}
/*
    检查该坑位是否被占，然后占领该坑位
*/
int64_t OG_API OgCrUniversalRegistrarAllocatePreallocatedItem(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                              uint32_t uPreAllocatedIndex, void **pOutput)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return (-1);
    }
    if (pur->uReservedItemCount < uPreAllocatedIndex + 1)
    {
        OgCrUniversalRegistrarReserveItems(pur, uPreAllocatedIndex + 1 - pur->uReservedItemCount);
    }
    if (pur->rgStatus[uPreAllocatedIndex])
    {
        OgCrSetRecoverableError(OPEN_STG_ERROR_CODE_CORE_MODULE_EXIST);
        return (-1);
    }
    pur->rgStatus[uPreAllocatedIndex] = TRUE;
    if (pOutput != NULL)
    {
        (*pOutput) = (BYTE_T *)pur->rgItems + uPreAllocatedIndex * pur->uUnitStructureSize;
    }
    return uPreAllocatedIndex;
}
BOOL_T OG_API OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint64_t uIndex)
{
    if (pur == NULL)
    {
        return (TRUE);
    }
    if (pur->uReservedItemCount - 1 < uIndex)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return (FALSE);
    }
    if (!pur->rgStatus[uIndex])
    {
        return (TRUE);
    }
    if (pur->pfDestoryMemberFunction != NULL)
    {
        pur->pfDestoryMemberFunction((BYTE_T *)pur->rgItems + uIndex * pur->uUnitStructureSize);
    }
    if ((pur->ufRegistrarFlag & OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED) == 0)
    {
        memset((void *)((BYTE_T *)pur->rgItems + uIndex * pur->uUnitStructureSize), 0, pur->uUnitStructureSize);
    }
    pur->rgStatus[uIndex] = FALSE;
    return (TRUE);
}
void *OG_API OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint64_t uIndex)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return NULL;
    }
    if (uIndex + 1 > pur->uReservedItemCount)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE));
        return NULL;
    }
    if (pur->rgStatus[uIndex])
    {
        return (BYTE_T *)pur->rgItems + pur->uUnitStructureSize * uIndex;
    }
    else
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MODULE_NOT_EXIST));
        return NULL;
    }
}
typedef struct TagOgCrUNIVERSAL_REGISTRAR_ITERATOR
{
    OG_CR_UNIVERSAL_REGISTRAR *pur;
    uint64_t uCurrentIndex;
    uint8_t uEnterTextHere;
} OG_CR_UNIVERSAL_REGISTRAR_ITERATOR;
OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return NULL;
    }
    OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri = NULL;
    if ((puri = (OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *)malloc(sizeof(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR))) == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return NULL;
    }
    puri->uCurrentIndex = 0;
    puri->uEnterTextHere = 0;
    puri->pur = pur;
    return puri;
}
void *OgCrUniversalRegistrarIteratorNext(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri)
{
    if (puri == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER));
        return FALSE;
    }
    OG_CR_UNIVERSAL_REGISTRAR *pur = puri->pur;
    void *pOutput = OgCrUniversalRegistrarGetItem(pur, puri->uCurrentIndex);
    for (uint64_t uIndex = puri->uCurrentIndex; uIndex < pur->uReservedItemCount; ++uIndex)
    {
        if (pur->rgStatus[uIndex])
        {
            puri->uCurrentIndex = uIndex;
            return pOutput;
        }
    }
    if (puri->uEnterTextHere < 1)
    {
        puri->uEnterTextHere++;
        return pOutput;
    }
    else
    {
        return NULL;
    }
}
void OgCrDestoryUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri)
{
    free((void *)puri);
}

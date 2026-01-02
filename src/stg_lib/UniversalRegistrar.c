#include "CloseStg.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct TagOgCrUNIVERSAL_REGISTRAR
{
    OG_CR_UNIVERSAL_REGISTRAR_FLAG_T ufRegistrarFlag;
    void *rgItems;
    BOOL_T *rgStatus;
    OG_DESTORY_MEMBER_FUNCTION_T pfDestoryMemberFunction;
    uint32_t uCountOfReservedItem; ///< rgItems和rgStatus的项数
    uint32_t uItemStructureSize;
} OG_CR_UNIVERSAL_REGISTRAR;

OG_CR_UNIVERSAL_REGISTRAR *OG_CDECL OgCrCreateUniversalRegistrar(const OG_CR_UNIVERSAL_REGISTRAR_INFORMATION *puri)
{
    if (puri == NULL || (puri->uItemStructureSize == 0 || puri->iSize < sizeof(OG_CR_UNIVERSAL_REGISTRAR)))
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return NULL;
    }
    OG_CR_UNIVERSAL_REGISTRAR *pur = (OG_CR_UNIVERSAL_REGISTRAR *)malloc(sizeof(OG_CR_UNIVERSAL_REGISTRAR));
    uint32_t uPreAllocatedCount = puri->uPreAllocatedCount, uItemStructureSize = puri->uItemStructureSize;
    void *rgItems = calloc(uPreAllocatedCount, uItemStructureSize);
    BOOL_T *rgStatus = (BOOL_T *)calloc(uPreAllocatedCount, sizeof(BOOL_T));
    if (rgItems == NULL || rgStatus == NULL || pur == NULL)
    {
        free(rgItems);
        free((void *)rgStatus);
        free((void *)pur);
    }
    memset((void *)pur, 0, sizeof(OG_CR_UNIVERSAL_REGISTRAR));
    memset(rgItems, 0, uPreAllocatedCount * uItemStructureSize);
    memset((void *)rgStatus, 0, uPreAllocatedCount);
    pur->rgItems = rgItems;
    pur->rgStatus = rgStatus;
    pur->uItemStructureSize = uItemStructureSize;
    pur->uCountOfReservedItem = uPreAllocatedCount;
    pur->pfDestoryMemberFunction = puri->pfDestoryMemberFunction;
    return (pur);
}
BOOL_T OG_CDECL OgCrUniversalRegistrarReserveItems(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uReserveCount)
{
    if (pur == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return (FALSE);
    }
    uint32_t uNewReserveCount = pur->uCountOfReservedItem + uReserveCount, uItemStructureSize = pur->uItemStructureSize;
    void *rgNewItems = NULL;
    if ((rgNewItems = realloc((void *)pur->rgItems, uNewReserveCount * uItemStructureSize)) == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return (FALSE);
    }
    BOOL_T *rgNewStatus = NULL;
    if ((rgNewStatus = (BOOL_T *)realloc((void *)pur->rgStatus, uNewReserveCount * sizeof(BOOL_T))) == NULL)
    {
        pur->rgItems = realloc((void *)pur->rgItems, pur->uCountOfReservedItem * uItemStructureSize);
        if (pur->rgItems)
        {
            // NOTE:一般不会运行到这里，如果运行到这里，这意味者系统的内存管理出现了错误，或者是这段代码的逻辑出现严重错误
            setCrIrreversibleError(OPEN_STG_ERROR_MESSAGE_UNDEFINED_MEMORY_ERROR);
            return (FALSE);
        }
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return (FALSE);
    }
    if ((pur->ufRegistrarFlag & 1) == 0)
    {
        void *pNewMomery = rgNewItems + uItemStructureSize * pur->uCountOfReservedItem;
        memset((void *)pNewMomery, 0x3B, uReserveCount * uItemStructureSize);
    }
    memset(rgNewStatus + pur->uCountOfReservedItem * sizeof(BOOL_T), 0, uReserveCount * sizeof(BOOL_T));
    pur->rgItems = rgNewItems;
    pur->rgStatus = rgNewStatus;
    pur->uCountOfReservedItem = uNewReserveCount;
    return (TRUE);
}
void OG_CDECL OgCrDestoryUniversalRegistrar(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        return;
    }
    BOOL_T bContinue = TRUE;
    for (uint32_t uIndex = 0, uMax = pur->uCountOfReservedItem; bContinue && uIndex < uMax; uIndex++)
    {
        bContinue &= OgCrUniversalRegistrarFreeItem(pur, uIndex);
    }
    free(pur->rgItems);
    free(pur->rgStatus);
}
int64_t OG_CDECL OgCrUniversalRegistrarAllocateItem(OG_CR_UNIVERSAL_REGISTRAR *pur, void **pOutput)
{
    if (pur == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return (-1);
    }
    for (uint32_t uIndex = 0, uMax = pur->uCountOfReservedItem; uIndex < uMax; uIndex++)
    {
        if (!pur->rgStatus[uIndex])
        {
            pur->rgStatus[uIndex] = TRUE;
            if (pOutput != NULL)
            {
                (*pOutput) = pur->rgItems + uIndex * pur->uItemStructureSize;
            }
            return uIndex;
        }
    }
    uint32_t uNextIndex = pur->uCountOfReservedItem;
    if (!OgCrUniversalRegistrarReserveItems(pur, 1))
    {
        return (-1);
    }
    pur->rgStatus[uNextIndex] = TRUE;
    if (pOutput != NULL)
    {
        (*pOutput) = pur->rgItems + uNextIndex * pur->uItemStructureSize;
    }
    return uNextIndex;
}
/*
    检查该坑位是否被占，然后占领该坑位
*/
int64_t OG_CDECL OgCrUniversalRegistrarAllocatePreallocatedItem(OG_CR_UNIVERSAL_REGISTRAR *pur,
                                                                uint32_t uPreAllocatedIndex, void **pOutput)
{
    if (pur == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return (-1);
    }
    if (pur->uCountOfReservedItem < uPreAllocatedIndex + 1)
    {
        OgCrUniversalRegistrarReserveItems(pur, uPreAllocatedIndex + 1 - pur->uCountOfReservedItem);
    }
    if (pur->rgStatus[uPreAllocatedIndex])
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MODULE_EXIST);
        return (-1);
    }
    pur->rgStatus[uPreAllocatedIndex] = TRUE;
    if (pOutput != NULL)
    {
        (*pOutput) = pur->rgItems + uPreAllocatedIndex * pur->uItemStructureSize;
    }
    return uPreAllocatedIndex;
}
BOOL_T OG_CDECL OgCrUniversalRegistrarFreeItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex)
{
    if (pur == NULL)
    {
        return (TRUE);
    }
    if (pur->uCountOfReservedItem - 1 < uIndex)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return (FALSE);
    }
    if (!pur->rgStatus[uIndex])
    {
        return (TRUE);
    }
    if (pur->pfDestoryMemberFunction != NULL)
    {
        pur->pfDestoryMemberFunction(pur->rgItems + uIndex * pur->uItemStructureSize);
    }
    if ((pur->ufRegistrarFlag & OPEN_STG_FLAG_UNIVERSAL_REGISTRAR_NOT_INITIALIZED) == 0)
    {
        memset((void *)(pur->rgItems + uIndex * pur->uItemStructureSize), 0, pur->uItemStructureSize);
    }
    pur->rgStatus[uIndex] = FALSE;
    return (TRUE);
}
void *OG_CDECL OgCrUniversalRegistrarGetItem(OG_CR_UNIVERSAL_REGISTRAR *pur, uint32_t uIndex)
{
    if (pur == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return NULL;
    }
    if (uIndex + 1 > pur->uCountOfReservedItem)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return NULL;
    }
    if (pur->rgStatus[uIndex])
    {
        return pur->rgItems + pur->uItemStructureSize * uIndex;
    }
    else
    {
        return NULL;
    }
}
typedef struct TagOgCrUNIVERSAL_REGISTRAR_ITERATOR
{
    OG_CR_UNIVERSAL_REGISTRAR *pur;
    uint32_t uCurrentIndex;
    uint32_t uEnterTextHere;
} OG_CR_UNIVERSAL_REGISTRAR_ITERATOR;
OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *OgCrCreateUniversalRegistrarIterator(OG_CR_UNIVERSAL_REGISTRAR *pur)
{
    if (pur == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return NULL;
    }
    OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *puri = NULL;
    if ((puri = (OG_CR_UNIVERSAL_REGISTRAR_ITERATOR *)malloc(sizeof(OG_CR_UNIVERSAL_REGISTRAR_ITERATOR))) == NULL)
    {
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
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
        setCrRecoverableError(OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER);
        return FALSE;
    }
    OG_CR_UNIVERSAL_REGISTRAR *pur = puri->pur;
    void *pOutput = OgCrUniversalRegistrarGetItem(pur, puri->uCurrentIndex);
    uint32_t uLastIndex = puri->uCurrentIndex;
    for (uint32_t uIndex = puri->uCurrentIndex; uIndex < pur->uCountOfReservedItem; ++uIndex)
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

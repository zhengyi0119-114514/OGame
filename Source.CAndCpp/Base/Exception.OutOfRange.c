#include "Exception.h"
#include <stdio.h>
#include <OpenSTG/OpenStgBase.String.h>
static const OgExceptionInformation s_eiOutOfRangeExcepitonInformation
    = {OgPrivateExceptionOutOfRangeDestroy,
       OgPrivateExceptionOutOfRangeFormatMessage,
       OgPrivateExceptionOutOfRangeGetFormattedMessageLength,
       NULL,
       NULL,
       OgExceptionOutOfRangeGetExceptionTypeName,
       OgPrivateExceptionOutOfRangeIsSomething};
// static OgException OgPrivateExceptionOutOfRangeFormatMessage(
//     const struct OgException *,
//     OgString psDestination,
//     OgUnsignedByte uDestinationSize);

OgBoolean OgPrivateExceptionOutOfRangeIsSomething(
    OgConstString pcsTypeName)
{
    return strcmp(pcsTypeName, OgExceptionOutOfRangeGetExceptionTypeName())
           == 0
           || OgPrivateExceptionLogicExceptionIsSomething(pcsTypeName);
}
void OgPrivateExceptionOutOfRangeDestroy(
    struct OgException e)
{
    free((OgPVoid)e.AdditionalData);
}
OgException OgExceptionThrowOutOfRangeV(
    OgConstString pcsParameter, OgConstString pcsMin, OgConstString pcsMax)
{
    // 设置并返回一个 OgPrivateExceptionOutOfRangeException 对象
    // 如果
    OgAllocator *aAllocator = OgAllocatorGetDefaultAllocator();
    OgBoolean bAllocatorUseable = OgFalse;
    OgPrivateExceptionOutOfRangeException *peThrownException = NULL;
    if (!OgExceptionIsNothing(
            OgAllocatorCheckBasic(aAllocator, &bAllocatorUseable)))
    {
        goto Fallback;
    }
    peThrownException = aAllocator->Alloc(
        aAllocator, sizeof(OgPrivateExceptionOutOfRangeException));
    if (peThrownException == NULL)
    {
        free((OgPVoid)peThrownException);
        goto Fallback;
    }
    memset(
        (OgPVoid)peThrownException, 0,
        sizeof(OgPrivateExceptionOutOfRangeException));
    if (pcsMin != NULL)
    {
        strncpy(
            peThrownException->Minimun, pcsMin,
            OPEN_STG_CONST_MINIMUN_STRING_LENGTH - 1);
    }
    if (pcsMax != NULL)
    {
        strncpy(
            peThrownException->Maximun, pcsMax,
            OPEN_STG_CONST_MAXIMUN_STRING_LENGTH - 1);
    }
    peThrownException->Type = OgExceptionTypeOutOfRange;
    ///  FIX: Update to new OgExceptionCreate

    // return OgExceptionCreate(&s_eiOutOfRangeExcepitonInformation,
    // (OgPVoid)peThrownException);
Fallback:
    ///  FIX: Update to new OgExceptionCreate

    // return OgExceptionCreate(NULL,
    // (OgPVoid)(OgIntPtr)OgExceptionTypeOutOfRange);
}
OgException OgExceptionThrowOutOfRangeD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter,
    OgConstString pcsMin,
    OgConstString pcsMax)
{
    OgException eBasicException
        = OgExceptionThrowOutOfRangeV(pcsParameter, pcsMin, pcsMax);
    if (eBasicException.Information == NULL)
    {
        return eBasicException;
    }
    OgPrivateExceptionOutOfRangeException *e
        = (OgPrivateExceptionOutOfRangeException *)
              eBasicException.AdditionalData;
    OgExceptionCreateBasicDebugInformation(e->Basic);
    return eBasicException;
}
OG_MACRO_PRIVATE void OgPrivateExceptionOutOfRangeDestroy(struct OgException e);
OG_MACRO_PRIVATE OgException OgPrivateExceptionOutOfRangeFormatMessage(
    const struct OgException eException,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize);
#define OgPrivateExceptionOutOfRangeFormatMessage_None "Type:%s\n"
#define OgPrivateExceptionOutOfRangeFormatMessage_MinimunOnly                  \
    "Type:%s\nMinimun:%s\n"
#define OgPrivateExceptionOutOfRangeFormatMessage_MaximunOnly                  \
    "Type:%s\nMaximun:%s\n"
#define OgPrivateExceptionOutOfRangeFormatMessage_All                          \
    "Type:%s\nMinimun:%s\nMaximun:%s\n"
OG_MACRO_PRIVATE OgException
    OgPrivateExceptionOutOfRangeGetFormattedMessageLength(
        const struct OgException e, OgUnsignedIntegerSize *puMessageSize)
{
    OgBoolean bHasMinimun = OgFalse, bHasMaximun = OgFalse;
    OgConstString pcsMinimun = OgStringGetEmptyString(),
                  pcsMaximun = OgStringGetEmptyString();
    OgPrivateExceptionOutOfRangeException *peAdditionalException = NULL;
    if (e.Information == NULL)
    {
        bHasMaximun = bHasMinimun = OgFalse;
        goto FormatMessage;
    }
    peAdditionalException
        = (OgPrivateExceptionOutOfRangeException *)e.AdditionalData;
    bHasMaximun = !OgStringIsNullOrEmpty(peAdditionalException->Maximun);
    bHasMinimun = !OgStringIsNullOrEmpty(peAdditionalException->Minimun);
    if (bHasMaximun)
    {
        pcsMaximun = peAdditionalException->Maximun;
    }
    if (bHasMinimun)
    {
        pcsMinimun = peAdditionalException->Minimun;
    }
FormatMessage:
    if (bHasMinimun && !bHasMaximun)
    {
        *puMessageSize = snprintf(
            NULL, 0, OgPrivateExceptionOutOfRangeFormatMessage_MinimunOnly,
            OgExceptionOutOfRangeGetExceptionTypeName(), pcsMaximun);
    }
    else if (!bHasMinimun && bHasMaximun)
    {
        *puMessageSize = snprintf(
            NULL, 0, OgPrivateExceptionOutOfRangeFormatMessage_MaximunOnly,
            OgExceptionOutOfRangeGetExceptionTypeName(), pcsMaximun);
    }
    else if (bHasMaximun && bHasMinimun)
    {
        *puMessageSize = snprintf(
            NULL, 0, OgPrivateExceptionOutOfRangeFormatMessage_All,
            OgExceptionOutOfRangeGetExceptionTypeName(), pcsMinimun,
            pcsMaximun);
    }
    else if (!bHasMaximun && !bHasMinimun)
    {
        *puMessageSize = snprintf(
            NULL, 0, OgPrivateExceptionOutOfRangeFormatMessage_None,
            OgExceptionOutOfRangeGetExceptionTypeName());
    }
    return OgExceptionThrowNothing();
}

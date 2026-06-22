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
       NULL};
// static OgException OgPrivateExceptionOutOfRangeFormatMessage(
//     const struct OgException *,
//     OgString psDestination,
//     OgUnsignedByte uDestinationSize);

OgBoolean OgPrivateExceptionOutOfRangeIsSomething(
    OgConstString pcsTypeName)
{
    return strcmp(pcsTypeName, OgExceptionOutOfRangeGetExceptionTypeName()) == 0
           || OgPrivateExceptionLogicExceptionIsSomething(pcsTypeName);
}
void OgPrivateExceptionOutOfRangeDestroy(
    struct OgException e)
{
    free(e.AdditionalData);
}
OgException OgExceptionThrowOutOfRangeV(
    OgConstString pcsParameter,
    OgConstString pcsMin,
    OgConstString pcsMax)
{
    OgAllocator aAllocator = OgAllocatorCreateCStandardAllocator();
    OgException e = OgExceptionThrowNothing();
    OgBoolean bAllocatorUseable = OgFalse;
    OgPrivateExceptionOutOfRangeException eThrownException, *peThrownException = NULL;
    e = OgAllocatorCheckBasic(&aAllocator, &bAllocatorUseable);
    if (bAllocatorUseable)
    {
        if (!OgExceptionIsNothing(e))
        {
            return e;
        }
        memset((OgPVoid)&eThrownException, 0, sizeof(OgPrivateExceptionOutOfRangeException));
        eThrownException.Type = OgExceptionTypeOutOfRange;
        if (pcsMin != NULL)
        {
            OgStringCopy(pcsMin, eThrownException.Minimun, OPEN_STG_CONST_MINIMUN_STRING_LENGTH);
        }
        if (pcsMax != NULL)
        {
            OgStringCopy(pcsMax, eThrownException.Maximun, OPEN_STG_CONST_MAXIMUN_STRING_LENGTH);
        }
        peThrownException = (OgPrivateExceptionOutOfRangeException *)aAllocator.Alloc(
            &aAllocator, sizeof(OgPrivateExceptionOutOfRangeException));
        if (peThrownException == NULL)
        {
            goto Fallback;
        }
        else
        {
            *peThrownException = eThrownException;
            return OgExceptionCreate(
                &s_eiOutOfRangeExcepitonInformation, (OgPVoid)peThrownException);
        }
    }
    else
    {
        goto Fallback;
    }
Fallback:
    return OgExceptionCreate(NULL, (OgPVoid)(OgIntPtr)OgExceptionTypeOutOfRange);
}
OgException OgExceptionThrowOutOfRangeD(
    OG_MACRO_THROW_EXCEPTION_EXTENSION_PARAMENT,
    OgConstString pcsParameter,
    OgConstString pcsMin,
    OgConstString pcsMax)
{
    OgException eBasicException = OgExceptionThrowOutOfRangeV(pcsParameter, pcsMin, pcsMax);
    if (eBasicException.Information == NULL)
    {
        return eBasicException;
    }
    OgPrivateExceptionOutOfRangeException *e
        = (OgPrivateExceptionOutOfRangeException *)eBasicException.AdditionalData;
    OgExceptionCreateBasicDebugInformation(e->Basic);
    return eBasicException;
}
OG_MACRO_PRIVATE void OgPrivateExceptionOutOfRangeDestroy(struct OgException e);
OG_MACRO_PRIVATE OgException OgPrivateExceptionOutOfRangeFormatMessage(
    const struct OgException *peException,
    OgString psDestination,
    OgUnsignedIntegerSize uDestinationSize);
OG_MACRO_PRIVATE OgException OgPrivateExceptionOutOfRangeGetFormattedMessageLength(
    const struct OgException *peException,
    OgUnsignedIntegerSize *puMessageSize);

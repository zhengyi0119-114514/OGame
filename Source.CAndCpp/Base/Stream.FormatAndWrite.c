#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>
#include <OpenSTG/OpenStgBase.Memory.h>
#include <pcre2.h>
#include "Stream.h"
#include "InlineFunctions.h"

OgMacroExtern struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteTextV(
    OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OgConstantString pcsFormat,
    va_list ptrArgument
)
{
    struct OgExceptionCollectionIoException e = {};
    OgString psBuffer = NULL;
    struct OgAllocator *a = OgMemoryAllocatorGetDefaultAllocator();
    int iResult = 0;
    size_t uStringLength = 0;
    OgBoolean bCanRead = OgFalse;
    // Check argument
    // 检查参数
    if (OgPrivateIsNull(pisStream))
    {
        struct OgExceptionCollectionIoException eReturn = {};
        eReturn.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        eReturn.InvalidArgument =
            OgExceptionStructureInvalidArgumentCreate("OgIoStream *pisStream", "Argument is null.");
        return (eReturn);
    }
    e = pisStream->GetBooleanProperty(
        pisStream, OgIoEnumStreamBooleanPropertyItemSupportReading, OgEnumBooleanOperatorItemOr,
        &bCanRead
    );
    switch (e.Type)
    {
        case OgExceptionEnumIoExceptionItemMemoryException:
        case OgExceptionEnumIoExceptionItemUndefineBehavior:
        case OgExceptionEnumIoExceptionItemOutOfRange:
        case OgExceptionEnumIoExceptionItemInvalidArgument: {
            OgExceptionPanic("Undefine Behavior");
            break;
        }
        default: {
            OgExceptionPanic("Undefine behavior.");
            break;
        }
    }
    if (!bCanRead)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgIoStream *pisStream", "Stream must be readable."
        );
        return (e);
    }
    if (pisStream->Write != NULL)

    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgIoStream *pisStream", "Stream must be readable."
        );
        return (e);
    }
    if (OgPrivateIsNull(pcsFormat))
    {
        OgExceptionCollectionIoException eReturn = {};
        eReturn.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        eReturn.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgConstantString pcsFormat", "Argument is null."
        );
        return (eReturn);
    }
    iResult = vsnprintf(NULL, 0, pcsFormat, ptrArgument);
    if (iResult < 0)
    {
        OgExceptionCollectionIoException eReturn = {};
        eReturn.Type = OgExceptionEnumIoExceptionItemUndefineBehavior;
        eReturn.UndefineBehavior =
            OgExceptionStructureUndefineBehaviorCreate("vsnprintf function return negative value.");
        return (eReturn);
    }
    uStringLength = (size_t)iResult + 1;
    psBuffer = a->Alloc(a, uStringLength);
    if (psBuffer == NULL)
    {
        OgExceptionCollectionIoException eReturn = {};
        eReturn.Type = OgExceptionEnumIoExceptionItemMemoryException;
        eReturn.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
        return (eReturn);
    }
    iResult = vsnprintf(psBuffer, uStringLength, pcsFormat, ptrArgument);
    if ((OgSignedInteger64)iResult != (OgSignedInteger64)(uStringLength - 1))
    {
        OgExceptionCollectionIoException eReturn = {};
        eReturn.Type = OgExceptionEnumIoExceptionItemUndefineBehavior;
        eReturn.UndefineBehavior =
            OgExceptionStructureUndefineBehaviorCreate("vsnprintf return negative value.");
        free(psBuffer);
        return (eReturn);
    }
    a->Free(a, psBuffer);
    OgExceptionCollectionIoException eReturn = {};
    return eReturn;
}

#include "Stream.h"
#include "InlineFunctions.h"

OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag)
{
    struct OgExceptionCollectionIoException e = {};
    struct OgPrivateIoMemoryStream msStream = {};
    struct OgPrivateIoMemoryStreamAdditionalData *pmsadAdditionalData = NULL;
    OgByte *pbBuffer = NULL;
    enum MemoryStreamLayout mslLayout = LayoutNone;
    // check argument.
    if (pStreamOutput == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgIoStream *const pStreamOutputr", "Argument is null.");
        return (e);
    }
    if (pAllocator == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgAllocator *const pAllocator", "Argument is null.");
        return (e);
    }
    if (uBufferSize > INT64_MAX)
    {
        e.Type = OgExceptionEnumIoExceptionItemOutOfRange;
        e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
            "uBufferSize", INT64_MAX, 0, "'uBytesToWrite' is too large.");
        return e;
    }
    msStream.Write = OgIoStreamMemoryStreamWrite;
    msStream.WriteBinary = OgIoStreamMemoryStreamWriteBinary;
    msStream.Read = OgIoStreamMemoryStreamRead;
    msStream.ReadBinary = OgIoStreamMemoryStreamReadBinary;
    msStream.GetBooleanProperty = OgIoStreamMemoryStreamGetBooleanProperty;
    msStream.SetBooleanProperty = OgIoStreamMemoryStreamSetBooleanProperty;
    msStream.GetIntegerProperty = OgIoStreamMemoryStreamGetIntegerProperty;
    msStream.SetIntegerProperty = OgIoStreamMemoryStreamSetIntegerProperty;
    msStream.Flush = OgIoStreamMemoryStreamFlush;
    msStream.Destroy = OgIoStreamMemoryStreamDestroy;
    msStream.Close = OgIoStreamMemoryStreamClose;
    if (iAlignment > 0)
    {
        if ((pAllocator->AlignedAlloc == NULL) || (pAllocator->AlignedFree == NULL))
        {
            e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
            e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
                "pAllocator->AlignedAlloc|AlginedFree", "Argument is null.");
            return (e);
            mslLayout = LayoutTowBlocksOfAlignedMemory;
        }
        if ((iemsfFlag | OgIoEnumMemoryStreamFlagItemAutoMovePosition) != 0)
        {
            e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
            e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
                "enum OgIoEnumMemoryStreamFlag iemsfFlag",
                "The size of an aligned memory stream cannot be changed.");
            return (e);
        }
    }
    else
    {
        if ((iemsfFlag | OgIoEnumMemoryStreamFlagItemAutoMovePosition) != 0)
        {
            mslLayout = LayoutTowBlocksOfMemory;
        }
        else
        {
            mslLayout = LayoutSingle;
        }
    }
    if ((pAllocator->Alloc == NULL) || (pAllocator->Free == NULL))
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "pAllocator->Alloc|Free", "Argument is null.");
        return (e);
    }
    switch (mslLayout)
    {
        case LayoutNone: {
            OgExceptionPanic("Undefine Behavior");
            break;
        }
        case LayoutSingle: {
            size_t uAdditionalDataSize =
                sizeof(struct OgPrivateIoMemoryStreamAdditionalData) + (size_t)uBufferSize;
            pmsadAdditionalData = (struct OgPrivateIoMemoryStreamAdditionalData *)pAllocator->Alloc(
                pAllocator, uAdditionalDataSize);
            if (pmsadAdditionalData == NULL)
            {
                pAllocator->AlignedFree(pAllocator, pbBuffer);
                pAllocator->Free(pAllocator, pmsadAdditionalData);
                e.Type = OgExceptionEnumIoExceptionItemMemoryException;
                e.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
                return e;
            }
            pbBuffer = pmsadAdditionalData->aBuffer;
            break;
        }
        case LayoutTowBlocksOfMemory: {
            pbBuffer = pAllocator->Alloc(pAllocator, (size_t)uBufferSize);
            pmsadAdditionalData = (struct OgPrivateIoMemoryStreamAdditionalData *)pAllocator->Alloc(
                pAllocator, sizeof(struct OgPrivateIoMemoryStreamAdditionalData));
            if (pbBuffer == NULL || pmsadAdditionalData == NULL)
            {
                pAllocator->AlignedFree(pAllocator, pbBuffer);
                pAllocator->Free(pAllocator, pmsadAdditionalData);
                e.Type = OgExceptionEnumIoExceptionItemMemoryException;
                e.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
                return e;
            }
            break;
        }
        case LayoutTowBlocksOfAlignedMemory: {
            pbBuffer = (OgByte *)pAllocator->AlignedAlloc(
                pAllocator, sizeof(uBufferSize), (OgUnsignedIntegerSize)iAlignment);
            pmsadAdditionalData = (struct OgPrivateIoMemoryStreamAdditionalData *)pAllocator->Alloc(
                pAllocator, sizeof(struct OgPrivateIoMemoryStreamAdditionalData));
            if (pbBuffer == NULL || pmsadAdditionalData == NULL)
            {
                pAllocator->AlignedFree(pAllocator, pbBuffer);
                pAllocator->Free(pAllocator, pmsadAdditionalData);
                e.Type = OgExceptionEnumIoExceptionItemMemoryException;
                e.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
                return e;
            }
            break;
        }
    }
    memset((OgPVoid)pbBuffer, 0, uBufferSize);
    memset((OgPVoid)pmsadAdditionalData, 0, sizeof(struct OgPrivateIoMemoryStreamAdditionalData));
    pmsadAdditionalData->pbBuffer = pbBuffer;
    pmsadAdditionalData->Alignment = iAlignment;
    pmsadAdditionalData->BufferSize = (OgSignedInteger64)uBufferSize;
    pmsadAdditionalData->Layout = mslLayout;
    msStream.psmsaData = (OgPVoid)pmsadAdditionalData;
    *pStreamOutput = *((struct OgIoStream *)&msStream);
    return e;
}
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile)
{
    struct OgExceptionCollectionIoException e = {};
    if (pisStream == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgIoStream *pisStream", "Argument is null.");
        return e;
    }
    if (strcmp(pisStream->GetStreamType(), OgIoStreamMemoryStreamGetStreamType()) == 0)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgIoStream *pisStream", "Stream Type does not match.");
        return e;
    }
    if (pbSource == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "const OgByte *psSourceBuffer", "Argument is null.");
        return e;
    }
    if (uBytesToWrite > INT64_MAX)
    {
        e.Type = OgExceptionEnumIoExceptionItemOutOfRange;
        e.OutOfRange = OgExceptionStructureOutOfRangeCreateWithInteger64(
            "OgUnsignedInteger64 uBytesToWrite", INT64_MAX, 0, "'uBytesToWrite' is too large.");
        return e;
    }
    {
        OgBoolean bResult = OgFalse;
        e = OgIoStreamMemoryStreamGetBooleanProperty(
            pisStream,
            (OgIoEnumStreamBooleanPropertyItemReachEndOfFile |
             OgIoEnumStreamBooleanPropertyItemIsClose),
            OgEnumBooleanOperatorItemOr, &bResult);
        if (e.Type != OgExceptionEnumIoExceptionItemNone)
        {
            return e;
        }
    }
    struct OgPrivateIoMemoryStream *pmsMemoryStream = (struct OgPrivateIoMemoryStream *)pisStream;
    struct OgPrivateIoMemoryStreamAdditionalData *pmsaData = pmsMemoryStream->psmsaData;
    OgSignedInteger64 iBytesWritten = pmsaData->BytesWritten;
    OgSignedInteger64 iAvailableMemorySize =
        (OgSignedInteger64)pmsaData->BufferSize - iBytesWritten;
    OgSignedInteger64 iBytesToWrite = 0;
    OgBoolean bEndOfFile = OgFalse;
    /// NOTE: 如果 pbSource 过长，则截断并返回EOF
    if (iAvailableMemorySize <= (OgSignedInteger64)uBytesToWrite)
    {
        iBytesToWrite = iAvailableMemorySize;
        bEndOfFile = OgTrue;
    }
    else
    {
        iBytesToWrite = (OgSignedInteger64)uBytesToWrite;
        bEndOfFile = OgFalse;
    }
    memcpy((OgPVoid)(pmsaData->pbBuffer + iBytesWritten), pbSource, (size_t)iBytesToWrite);
    iBytesWritten += iBytesToWrite;
    pmsaData->BytesWritten = iBytesWritten;
    *pbEndOfFile = bEndOfFile;
    return e;
}
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgCharacter *psSourceBuffer,
    OgUnsignedInteger64 uCharatcterToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXPORT OgConstantString OgIoStreamMemoryStreamGetStreamType(
    void)
{
    return ("OpenStg.Base.IO.MemoryStream");
}

#include "Stream.h"
#include "InlineFunctions.h"

struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const paAllocator,
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
    if (paAllocator == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgAllocator *const paAllocator", "Argument is null.");
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
    if (iAlignment >= 0)
    {
        if ((paAllocator->AlignedAlloc == NULL) || (paAllocator->AlignedFree == NULL))
        {
            e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
            e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
                "paAllocator->AlignedAlloc|AlginedFree", "Argument is null.");
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
    if ((paAllocator->Alloc == NULL) || (paAllocator->Free == NULL))
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "paAllocator->Alloc|Free", "Argument is null.");
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
            pmsadAdditionalData =
                (struct OgPrivateIoMemoryStreamAdditionalData *)paAllocator->Alloc(
                    paAllocator, uAdditionalDataSize);
            if (pmsadAdditionalData == NULL)
            {
                paAllocator->AlignedFree(paAllocator, pbBuffer);
                paAllocator->Free(paAllocator, pmsadAdditionalData);
                e.Type = OgExceptionEnumIoExceptionItemMemoryException;
                e.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
                return e;
            }
            pbBuffer = pmsadAdditionalData->aBuffer;
            break;
        }
        case LayoutTowBlocksOfMemory: {
            pbBuffer = paAllocator->Alloc(paAllocator, (size_t)uBufferSize);
            pmsadAdditionalData =
                (struct OgPrivateIoMemoryStreamAdditionalData *)paAllocator->Alloc(
                    paAllocator, sizeof(struct OgPrivateIoMemoryStreamAdditionalData));
            if (pbBuffer == NULL || pmsadAdditionalData == NULL)
            {
                paAllocator->AlignedFree(paAllocator, pbBuffer);
                paAllocator->Free(paAllocator, pmsadAdditionalData);
                e.Type = OgExceptionEnumIoExceptionItemMemoryException;
                e.MemoryException = OgExceptionStructureMemoryExceptionCreateOutOfMemory();
                return e;
            }
            break;
        }
        case LayoutTowBlocksOfAlignedMemory: {
            pbBuffer = (OgByte *)paAllocator->AlignedAlloc(
                paAllocator, sizeof(uBufferSize), (OgUnsignedIntegerSize)iAlignment);
            pmsadAdditionalData =
                (struct OgPrivateIoMemoryStreamAdditionalData *)paAllocator->Alloc(
                    paAllocator, sizeof(struct OgPrivateIoMemoryStreamAdditionalData));
            if (pbBuffer == NULL || pmsadAdditionalData == NULL)
            {
                paAllocator->AlignedFree(paAllocator, pbBuffer);
                paAllocator->Free(paAllocator, pmsadAdditionalData);
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
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile)
{
    struct OgExceptionCollectionIoException e = {};
    OgBoolean bStreamUseable = OgFalse;
    OgBoolean bStreamAutoResize = OgFalse;
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
    e = OgIoStreamMemoryStreamGetBooleanProperty(
        pisStream,
        (OgIoEnumStreamBooleanPropertyItemReachEndOfFile |
         OgIoEnumStreamBooleanPropertyItemIsClose),
        OgEnumBooleanOperatorItemOr, &bStreamUseable);
    if (e.Type != OgExceptionEnumIoExceptionItemNone)
    {
        return e;
    }
    if (!bStreamUseable)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "struct OgIoStream *pisStream",
            "Stream must not be closed and have reached the end of the file.");
        return e;
    }
    e = OgIoStreamMemoryStreamGetBooleanProperty(
        pisStream, OgIoEnumStreamBooleanPropertyItemIsClose, OgEnumBooleanOperatorItemOr,
        &bStreamAutoResize);
    if (e.Type != OgExceptionEnumIoExceptionItemNone)
    {
        return e;
    }
    if (bStreamAutoResize)
    {
        struct OgPrivateIoMemoryStream *pmsMemoryStream =
            (struct OgPrivateIoMemoryStream *)pisStream;
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
    }
    else
    {
        OgExceptionPanic("Not implemented.");
    }
    return e;
}
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatcterToWrite,
    OgBoolean *const pbEndOfFile)
{
    struct OgExceptionCollectionIoException e = {};
#if defined(_WIN32)
    /// TODO: finish it in windows.
#else
    OgSignedInteger64 iBytesToWrite = 0;
    if (pcsSource == NULL)
    {
        e.Type = OgExceptionEnumIoExceptionItemInvalidArgument;
        e.InvalidArgument = OgExceptionStructureInvalidArgumentCreate(
            "OgConstantString pcsSource", "Argument is null.");
        return e;
    }
    if (iCharatcterToWrite >= 0)
    {
        iBytesToWrite = iCharatcterToWrite;
    }
    else
    {
        iBytesToWrite = (OgSignedInteger64)strlen(pcsSource);
    }
    return OgIoStreamMemoryStreamWriteBinary(
        pisStream, (const OgByte *)pcsSource, (OgUnsignedInteger64)iBytesToWrite, pbEndOfFile);
#endif
}
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    struct OgIoStream *const pisStream, OgBoolean bCleanBuffer)
{
    struct OgExceptionCollectionIoException e = {};
    return e;
}
OgConstantString OgIoStreamMemoryStreamGetStreamType(
    void)
{
    return ("OpenStg.Base.IO.MemoryStream");
}

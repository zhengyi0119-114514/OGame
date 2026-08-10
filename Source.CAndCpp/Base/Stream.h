#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#include <assert.h>
// #include <windows.h>

#if !defined(OPEN_STG_STREAM_H)
#define OPEN_STG_STREAM_H 1
OgMacroCBlockEnd

OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutputr,
    struct OgAllocator *const paAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag
);

OgMacroExport struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteTextV(
    OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OgConstantString pcsFormat,
    va_list ptrArgument
);

enum MemoryStreamLayout
{
    LayoutNone,
    LayoutSingle,
    LayoutTowBlocksOfMemory,
    LayoutTowBlocksOfAlignedMemory,
};
struct OgPrivateIoMemoryStreamAdditionalData
{
    OgPointerSizedUnsignedInteger uAlign;
    OgPointerSizedUnsignedInteger uBufferSize;
    OgPointerSizedUnsignedInteger uReadPositionIndicator;
    OgPointerSizedUnsignedInteger uWritePositionIndicator;
    OgByte *pbBuffer;
    alignas(alignof(OgPointerSizedUnsignedInteger)) OgByte aBuffer[];
};
OgMacroExport OgConstantString OgIoStreamMemoryStreamGetStreamType(void);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const paAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    struct OgIoStream *const pisStream,
    OgByte *const pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 uBytesToRead,
    OgUnsignedInteger64 *const puBytesRead,
    OgBoolean *const pbEndOfFile
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    struct OgIoStream *const pisStream,
    OgCharacter *const psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 uBufferSize,
    OgBoolean *const pbEndOfFile
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *const pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatcterToWrite,
    OgBoolean *const pbEndOfFile
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetBooleanProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamBooleanProperty sbpProperty,
    enum OgEnumBitFlagOperator bfoOperator,
    OgBoolean *const pbOut
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetBooleanProperty(
    struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty sbpProperty
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetIntegerProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgSignedInteger64 *const piOut
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetIntegerProperty(
    struct OgIoStream *const pisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgUnsignedInteger64 iValue
);
OgMacroExport struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    struct OgIoStream *const pisStream, OgBoolean bCleanBuffer
);
OgMacroExport void OgIoStreamMemoryStreamClose(struct OgIoStream *const pisStream);
OgMacroExport void OgIoStreamMemoryStreamDestroy(struct OgIoStream *const pisStream);

OgMacroCBlockEnd
#endif

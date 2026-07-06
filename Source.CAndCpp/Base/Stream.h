#include <OpenSTG/OpenStgBase.InputAndOutput.h>
#include <assert.h>

#if !defined(OPEN_STG_STREAM_H)
#define OPEN_STG_STREAM_H 1
OG_MACRO_C_BLOCK_END

OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutputr,
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag);

OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteTextV(
    OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OgConstantString pcsFormat,
    va_list ptrArgument);

enum MemoryStreamLayout
{
    LayoutNone,
    LayoutSingle,
    LayoutTowBlocksOfMemory,
    LayoutTowBlocksOfAlignedMemory
};
struct OgPrivateIoMemoryStreamAdditionalData
{
    OgSignedInteger64 BytesWritten;
    OgSignedInteger64 Alignment;
    OgSignedInteger64 BufferSize;
    enum MemoryStreamLayout Layout;
    OgByte *pbBuffer;
    alignas(alignof(OgSignedInteger64)) OgByte aBuffer[];
};
struct OgPrivateIoMemoryStream
{
    OgConstantString (*GetStreamType)(void);
    struct OgExceptionCollectionIoException (*ReadBinary)(
        struct OgIoStream *const pisStream,
        OgByte *pbBuffer,
        OgUnsignedInteger64 uBufferSize,
        OgUnsignedInteger64 *const uBytesRead,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*Read)(
        struct OgIoStream *const pisStream,
        OgCharacter *psDestinationBuffer,
        OgUnsignedInteger64 uDestinationBufferSize,
        OgUnsignedInteger64 *const uBytesRead,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*WriteBinary)(
        struct OgIoStream *pisStream,
        const OgByte *const pbSource,
        OgUnsignedInteger64 uBytesToWrite,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*Write)(
        struct OgIoStream *pisStream,
        OgCharacter *psSourceBuffer,
        OgUnsignedInteger64 uCharatcterToWrite,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*GetBooleanProperty)(
        const struct OgIoStream *const pcisStream,
        enum OgIoEnumStreamBooleanProperty sbpProperty,
        enum OgEnumBitFlagOperator bfoOperator,
        OgBoolean *const pbOut);
    struct OgExceptionCollectionIoException (*SetBooleanProperty)(
        struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty);
    struct OgExceptionCollectionIoException (*GetIntegerProperty)(
        const struct OgIoStream *const pcisStream,
        enum OgIoEnumStreamIntegerProperty,
        OgSignedInteger64 *const piOut);
    struct OgExceptionCollectionIoException (*SetIntegerProperty)(
        struct OgIoStream *const pisStream,
        enum OgIoEnumStreamIntegerProperty,
        OgUnsignedInteger64 iValue);
    struct OgExceptionCollectionIoException (*Flush)(
        struct OgIoStream *const pisStream, OgBoolean bCleanBuffer);
    void (*Close)(struct OgIoStream *const pisStream);
    void (*Destroy)(struct OgIoStream *const pisStream);
    union
    {
        OgPVoid AdditionalData;
        struct OgPrivateIoMemoryStreamAdditionalData *psmsaData;
    };
};
static_assert(
    sizeof(struct OgIoStream) == sizeof(struct OgPrivateIoMemoryStream),
    "The size of OgIoMemoryStream structure donot equals the size of OgIoStream structure.");

OG_MACRO_EXPORT OgConstantString OgIoStreamMemoryStreamGetStreamType(void);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    struct OgIoStream *const pisStream,
    OgByte *pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 *const uBytesRead,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    struct OgIoStream *const pisStream,
    OgCharacter *psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 *const uBufferSize,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *const pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgCharacter *psSourceBuffer,
    OgUnsignedInteger64 uCharatcterToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetBooleanProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamBooleanProperty sbpProperty,
    enum OgEnumBitFlagOperator bfoOperator,
    OgBoolean *const pbOut);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetBooleanProperty(
    struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetIntegerProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgSignedInteger64 *const piOut);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetIntegerProperty(
    struct OgIoStream *const pisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgUnsignedInteger64 iValue);
OG_MACRO_EXPORT struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    struct OgIoStream *const pisStream, OgBoolean bCleanBuffer);
OG_MACRO_EXPORT void OgIoStreamMemoryStreamClose(struct OgIoStream *const pisStream);
OG_MACRO_EXPORT void OgIoStreamMemoryStreamDestroy(struct OgIoStream *const pisStream);

OG_MACRO_C_BLOCK_END
#endif

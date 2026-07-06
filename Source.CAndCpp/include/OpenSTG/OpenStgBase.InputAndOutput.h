#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>
#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H)
#define OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H 1
#include <OpenSTG/OpenStgBase.Exceptions.h>
#include <OpenSTG/OpenStgBase.Memory.h>

OG_MACRO_C_BLOCK_BEGIN

// NOTE: Base on https://learn.microsoft.com/en-us/dotnet/api/system.io.stream

typedef enum OgIoEnumStreamBooleanProperty
{
    OgIoEnumStreamBooleanPropertyItemNone = 0,
    OgIoEnumStreamBooleanPropertyItemSupportReading = 0x00000001,
    OgIoEnumStreamBooleanPropertyItemSupportWriting = 0x00000002,
    OgIoEnumStreamBooleanPropertyItemSupportAsynchronousOperation = 0x00000004,
    OgIoEnumStreamBooleanPropertyItemSupportRandomReadingAndRedomWriting = 0x00000008,
    OgIoEnumStreamBooleanPropertyItemSupportReflush = 0x00000010,
    OgIoEnumStreamBooleanPropertyItemHasBuffer = 0x00000020,
    OgIoEnumStreamBooleanPropertyItemHasLock = 0x00000040, /// TODO: After task module.
    OgIoEnumStreamBooleanPropertyItemIsThreadSafety = 0x00000080,
    OgIoEnumStreamBooleanPropertyItemIsClose = 0x00000100,
    OgIoEnumStreamBooleanPropertyItemIsAsynchronous = 0x00000200,
    OgIoEnumStreamBooleanPropertyItemReachEndOfFile = 0x00000400,
} OgIoEnumStreamBooleanProperty;

typedef enum OgIoEnumStreamIntegerProperty
{
    OgIoEnumStreamIntegerPropertyItemNone = 0,
    OgIoEnumStreamIntegerPropertyItemBufferLength = 1,
    OgIoEnumStreamIntegerPropertyItemLength = 2,
    OgIoEnumStreamIntegerPropertyItemPosition = 3,
    OgIoEnumStreamIntegerPropertyItemReadTimeOut = 4,
    OgIoEnumStreamIntegerPropertyItemWriteTimeOut = 5,
} OgIoEnumStreamIntegerProperty;

typedef enum OgIoEnumStreamPVoidProperty
{
    OgIoEnumStreamPVoidPropertyItemNone = 0,
    OgIoEnumStreamPVoidPropertyItemBuffer = 1,
} OgIoEnumStreamPVoidProperty;
typedef struct OgIoStream
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
    OgPVoid AdditionalData;
} OgIoStream;

typedef enum OgIoEnumSystemStream
{
    OgIoEnumSystemStreamItemStandardNone = 0,
    OgIoEnumSystemStreamItemStandardInput = 1,
    OgIoEnumSystemStreamItemStandardOutput = 2,
    OgIoEnumSystemStreamItemStandardErrorOutput = 3,
} OgIoEnumSystemStream;

OG_MACRO_EXTERN struct OgIoStream *OgIoStreamGetStandardStream(
    enum OgIoEnumSystemStream const isessType);

typedef enum OgIoEnumFormatAndWriteTextFlags
{
    OgIoEnumFormatAndWriteTextFlagsItemNone = 0x00000000,
    // OgIoEnumFormatAndWriteTextFlagsItemDisableSafeOption = 0x00000001,
} OgIoEnumFormatAndWriteTextFlags;

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteTextV(
    OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OgConstantString pcsFormat,
    va_list ptrArgument);
inline struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteText(
    OgIoStream *pisStream, OgUnsignedInteger64 uFormatFlag, OgConstantString pcsFormat, ...);

typedef enum OgIoEnumMemoryStreamFlag
{
    OgIOEnumMemoryStreamFlagItemNone = 0x00000000,
    OgIOEnumMemoryStreamFlagItemAutomaticMemoryGrowth = 0x00000001,
    OgIOEnumMemoryStreamFlagItemCanSeek = 0x00000002,
    OgIoEnumMemoryStreamFlagItemAutoMovePosition = 0x00000004,
    OgIoEnumMemoryStreamFlagItemEnableLock = 0x00000008, /// TODO: after task module.
} OgIOEnumMemoryStreamFlag;

OG_MACRO_EXTERN OgConstantString OgIoStreamMemoryStreamGetStreamType(void);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    struct OgIoStream *const pisStream,
    OgByte *pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 *const uBytesRead,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    struct OgIoStream *const pisStream,
    OgCharacter *psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 *const uBufferSize,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *const pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgCharacter *psSourceBuffer,
    OgUnsignedInteger64 uCharatcterToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetBooleanProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamBooleanProperty sbpProperty,
    enum OgEnumBitFlagOperator bfoOperator,
    OgBoolean *const pbOut);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetBooleanProperty(
    struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetIntegerProperty(
    const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgSignedInteger64 *const piOut);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetIntegerProperty(
    struct OgIoStream *const pisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgUnsignedInteger64 iValue);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    struct OgIoStream *const pisStream, OgBoolean bCleanBuffer);
OG_MACRO_EXTERN void OgIoStreamMemoryStreamClose(struct OgIoStream *const pisStream);
OG_MACRO_EXTERN void OgIoStreamMemoryStreamDestroy(struct OgIoStream *const pisStream);

OG_MACRO_C_BLOCK_END
#endif

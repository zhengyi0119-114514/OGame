#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H)
#define OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_H 1
#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>

OG_MACRO_C_BLOCK_BEGIN

/// NOTE: Base on https://learn.microsoft.com/en-us/dotnet/api/system.io.stream
typedef enum OgIoEnumStreamBooleanProperty
{
    OgIoEnumStreamBooleanPropertyItemCanRead = 1,
    OgIoEnumStreamBooleanPropertyItemCanWrite = 2,
    OgIoEnumStreamBooleanPropertyItemCanSeek = 3, /// TODO: Finish it
    OgIoEnumStreamBooleanPropertyItemCanReflush = 4,
    OgIoEnumStreamBooleanPropertyItemHasBuffer = 5,
    OgIoEnumStreamBooleanPropertyItemIsThreadSafety = 6,
    OgIoEnumStreamBooleanPropertyItemSupportAsync = 7,
    OgIoEnumStreamBooleanPropertyItemReachEndOfFile = 8,
    OgIoEnumStreamBooleanPropertyItemIsClosed = 9,
} OgIoEnumStreamProperty;

typedef enum OgIoEnumStreamIntegerProperty
{
    OgIoEnumStreamIntegerPropertyItemNone = 0,
    OgIoEnumStreamIntegerPropertyItemBufferLength = 1,
    OgIoEnumStreamIntegerPropertyItemSeek = 2,
} OgIoEnumStreamIntegerProperty;

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
        OgUnsignedInteger64 *const uBufferSize,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*WriteBinary)(
        struct OgIoStream *pisStream,
        OgByte *psSourceBuffer,
        OgUnsignedInteger64 uBytesToWrite,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*Write)(
        struct OgIoStream *pisStream,
        OgCharacter *psSourceBuffer,
        OgUnsignedInteger64 uCharatcterToWrite,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*GetBooleanProperty)(
        const struct OgIoStream *const pcisStream,
        enum OgIoEnumStreamBooleanProperty,
        OgBoolean *const pbOut);
    struct OgExceptionCollectionIoException (*SetBooleanProperty)(
        struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty, OgBoolean bValue);
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
    OgPVoid AdditionalData2;
    OgPVoid AdditionalData3;
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

typedef enum OgIoEnumMemeryStreamFlag
{
    OgIOEnumMemeryStreamFlagItemNone = 0x00000000,
    OgIOEnumMemeryStreamFlagItemAutomaticMemoryGrowth = 0x00000001,
    OgIOEnumMemeryStreamFlagItemCanSeek = 0x00000002,
} OgIOEnumMemeryStreamFlag;
OG_MACRO_EXTERN struct OgIoStream OgIoStreamCreateMemeryStream(
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemeryStreamFlag iemsfFlag);

OG_MACRO_C_BLOCK_END
#endif

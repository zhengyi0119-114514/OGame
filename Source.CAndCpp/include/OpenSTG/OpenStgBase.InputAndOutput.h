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
        OgUnsignedInteger64 uBytesRead,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*Read)(
        struct OgIoStream *const pisStream,
        OgCharacter *psDestinationBuffer,
        OgUnsignedInteger64 uDestinationBufferSize,
        OgUnsignedInteger64 uBytesRead,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*WriteBinary)(
        struct OgIoStream *pisStream,
        const OgByte *const pbSource,
        OgUnsignedInteger64 uBytesToWrite,
        OgBoolean *const pbEndOfFile);
    struct OgExceptionCollectionIoException (*Write)(
        struct OgIoStream *pisStream,
        OgConstantString pcsSource,
        OgSignedInteger64 uCharatcterToWrite,
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

/**
 * @brief Return the string "OpenStg.Base.IO.MemoryStream".
 *
 * @return Always "OpenStg.Base.IO.MemoryStream"
 */
OG_MACRO_EXTERN OgConstantString OgIoStreamMemoryStreamGetStreamType(void);
/**
 * @brief Create a stream whose backing is memory.
 *
 * @param pStreamOutput output.
 * @param paAllocator Strategies for access/addressing and allocation/deallocatio of object.
 * @param iAlignment Specify the alignment.Must be a valid alignment supported by the
 * implementation.Default: -1.
 * @param uBufferSize Number of bytes to allocate.If iAlignment is not -1,It must be an integer
 * multiple if iAlignment.
 * @param iemsfFlag A set of OgIoEnumMemoryStreamFlag flag.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const paAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag);
/**
 * @brief Read sequence of bytes from current stream and advances the position within the stream by
 * the number of bytes read .
 *
 * @param pisStream Output stream to write to.
 * @param pbBuffer A byte array to the bytes from the stream to be read .
 * @param uBufferSize Maximum number of bytes than can be read from the stream.
 * @param uBytesRead A number of the bytes to be read.
 * @param pbEndOfFile A pointer to a boolean variable that determine whether the end of the stream
 * has Been reached .
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    struct OgIoStream *const pisStream,
    OgByte *pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 uBytesRead,
    OgBoolean *const pbEndOfFile);
/**
 * @brief Read sequence of bytes from current stream and advances the position within the stream by
 * the number of bytes read.
 *
 * @param pisStream The stream to write to.
 * @param psDestinationBuffer A array of character to the character from the stream to be read.
 * @param uDestinationBufferSize Maximum number of character that can be read from the stream.
 * @param uCharactersRead The number of the character to be read.
 * @param pbEndOfFile A pointer to a boolean variable that determine whether the end of the stream
 * has Been reached .
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    struct OgIoStream *const pisStream,
    OgCharacter *psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 uCharactersRead,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *const pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile);
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatcterToWrite,
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

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
    OgIoEnumStreamIntegerPropertyItemPositionIndicator = 3,
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
        OgBoolean *const pbEndOfFile
    );
    struct OgExceptionCollectionIoException (*Read)(
        struct OgIoStream *const pisStream,
        OgCharacter *psDestinationBuffer,
        OgUnsignedInteger64 uDestinationBufferSize,
        OgUnsignedInteger64 uBytesRead,
        OgBoolean *const pbEndOfFile
    );
    struct OgExceptionCollectionIoException (*WriteBinary)(
        struct OgIoStream *pisStream,
        const OgByte *const pbSource,
        OgUnsignedInteger64 uBytesToWrite,
        OgBoolean *const pbEndOfFile
    );
    struct OgExceptionCollectionIoException (*Write)(
        struct OgIoStream *pisStream,
        OgConstantString pcsSource,
        OgSignedInteger64 uCharatcterToWrite,
        OgBoolean *const pbEndOfFile
    );
    struct OgExceptionCollectionIoException (*GetBooleanProperty)(
        const struct OgIoStream *const pcisStream,
        enum OgIoEnumStreamBooleanProperty sbpProperty,
        enum OgEnumBitFlagOperator bfoOperator,
        OgBoolean *const pbOut
    );
    struct OgExceptionCollectionIoException (*SetBooleanProperty)(
        struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty
    );
    struct OgExceptionCollectionIoException (*GetIntegerProperty)(
        const struct OgIoStream *const pcisStream,
        enum OgIoEnumStreamIntegerProperty,
        OgSignedInteger64 *const piOut
    );
    struct OgExceptionCollectionIoException (*SetIntegerProperty)(
        struct OgIoStream *const pisStream,
        enum OgIoEnumStreamIntegerProperty,
        OgUnsignedInteger64 iValue
    );
    struct OgExceptionCollectionIoException (*Flush)(
        struct OgIoStream *const pisStream, OgBoolean bCleanBuffer
    );
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
    enum OgIoEnumSystemStream const isessType
);

typedef enum OgIoEnumFormatAndWriteTextFlags
{
    OgIoEnumFormatAndWriteTextFlagsItemNone = 0x00000000,
    // OgIoEnumFormatAndWriteTextFlagsItemDisableSafeOption = 0x00000001,
} OgIoEnumFormatAndWriteTextFlags;

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteTextV(
    OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OG_MACRO_MSVC(_Printf_format_string_) OgConstantString pcsFormat,
    va_list ptrArgument
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 3));

inline struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteText(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *pisStream,
    OgUnsignedInteger64 uFormatFlag,
    OG_MACRO_MSVC(_Printf_format_string_) OgConstantString pcsFormat,
    ...
) OG_MACRO_GNU_ATTRIBUTE(__format__(printf, 3, 4), __nonnull__(1, 3), __always_inline__);

typedef enum OgIoEnumMemoryStreamFlag
{
    OgIOEnumMemoryStreamFlagItemNone = 0x00000000,
    OgIOEnumMemoryStreamFlagItemAutomaticMemoryGrowth = 0x00000001,
    OgIOEnumMemoryStreamFlagItemCanSeek = 0x00000002,
    OgIoEnumMemoryStreamFlagItemAutoMovePosition = 0x00000004,
    OgIoEnumMemoryStreamFlagItemEnableLock = 0x00000008, /// TODO: after task module.
    OgIoEnumMemoryStreamFlagItemEnableTransform = 0x00000010,
} OgIOEnumMemoryStreamFlag;

/**
 * @brief Return the string "OpenStg.Base.IO.MemoryStream".
 * @retval "OpenStg.Base.IO.MemoryStream"
 */
OG_MACRO_EXTERN OgConstantString OgIoStreamMemoryStreamGetStreamType(void);
/**
 * @brief Create a stream whose backing is memory.
 *
 * @param[in] pStreamOutput output.
 * @param[in] paAllocator Strategies for access/addressing and allocation/deallocatio of object.
 * @param iAlignment Specify the alignment.Must be a valid alignment supported by the
 * implementation.Default: -1.
 * @param uBufferSize Number of bytes to allocate.If iAlignment is not -1,It must be an integer
 * multiple if iAlignment.
 * @param iemsfFlag A set of OgIoEnumMemoryStreamFlag flag.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    OG_MACRO_MSVC(_Out_) struct OgIoStream *const pStreamOutput,
    OG_MACRO_MSVC(_In_) struct OgAllocator *const paAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 2));
/**
 * @brief Read sequence of bytes from current stream.The file position indicator for the stream is
 * advanced by the number of characters written.
 *
 * @param[in] pisStream Output stream to read.
 * @param[out] pbBuffer A byte array to the bytes from the stream to be read.
 * @param uBufferSize Maximum number of bytes than can be read from the stream.
 * @param uBytesToRead A number of the bytes to be read.
 * @param[out] puBytesRead A pointer to a unsigned integer variable used to store the number of
 * bytes read.
 * @param[out] pbEndOfFile A pointer to a boolean variable that determine whether the end of the
 * stream has Been reached.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream,
    OG_MACRO_MSVC(_Out_) OgByte *const pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 uBytesToRead,
    OG_MACRO_MSVC(_Out_opt_) OgUnsignedInteger64 *const puBytesRead,
    OG_MACRO_MSVC(_Out_opt_) OgBoolean *const pbEndOfFile
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 2));
/**
 * @brief Read sequence of bytes from current stream.The file position indicator for the stream is
 * advanced by the number of characters written.
 *
 * @param pisStream The stream to read.
 * @param[out] psDestinationBuffer A array of character to the character from the stream to be read.
 * @param uDestinationBufferSize Maximum number of character that can be read from the stream.
 * @param uCharactersRead The number of the characters to be read.
 * @param[out] pbEndOfFile A pointer to a boolean variable that determine whether the end of the
 * stream has been reached.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream,
    OG_MACRO_MSVC(_Out_) OgCharacter *const psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 uCharactersRead,
    OG_MACRO_MSVC(_Out_opt_) OgBoolean *const pbEndOfFile
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 2));
/**
 * @brief Writes a block of bytes to the current stream using data read from stream.
 * The file position indicator for the stream is advanced by the number of characters written.
 *
 * @param pisStream The stream to write.
 * @param[in] pbSource A array of characters to write data.
 * @param uBytesToWrite The number of bytes to write.
 * @param[out] pbEndOfFile A pointer to a Boolean variable that determine whether the end of the
 * stream has been reached.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream,
    OG_MACRO_MSVC(_In_) const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OG_MACRO_MSVC(_Out_opt_) OgBoolean *const pbEndOfFile
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 2));
/**
 * @brief Writes a string to the current stream.The file position indicator for the stream is
 * advanced by the number of characters written.
 *
 * @param pisStream The stream to write.
 * @param[in] pcsSource A string to write data.
 * @param iCharatctersToWrite The length of string to write.If it less than 0,write the entire
 * string.
 * @param[out] pbEndOfFile A pointer to a Boolean variable that determine whether the end of the
 * stream.
 */
OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream,
    OG_MACRO_MSVC(_In_) OgConstantString pcsSource,
    OgSignedInteger64 iCharatctersToWrite,
    OG_MACRO_MSVC(_Out_opt_) OgBoolean *const pbEndOfFile
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 4));

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetBooleanProperty(
    OG_MACRO_MSVC(_In_) const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamBooleanProperty sbpProperty,
    enum OgEnumBitFlagOperator bfoOperator,
    OG_MACRO_MSVC(_Out_) OgBoolean *const pbOut
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 4));

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetBooleanProperty(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pcisStream, enum OgIoEnumStreamBooleanProperty
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1));

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamGetIntegerProperty(
    OG_MACRO_MSVC(_In_) const struct OgIoStream *const pcisStream,
    enum OgIoEnumStreamIntegerProperty,
    OG_MACRO_MSVC(_Out_) OgSignedInteger64 *const piOut
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1, 3));

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamSetIntegerProperty(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream,
    enum OgIoEnumStreamIntegerProperty,
    OgUnsignedInteger64 iValue
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1));

OG_MACRO_EXTERN struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    OG_MACRO_MSVC(_Inout_) struct OgIoStream *const pisStream, OgBoolean bCleanBuffer
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1));

OG_MACRO_EXTERN void OgIoStreamMemoryStreamClose(
    struct OgIoStream *const pisStream
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1));

OG_MACRO_EXTERN void OgIoStreamMemoryStreamDestroy(
    struct OgIoStream *const pisStream
) OG_MACRO_GNU_ATTRIBUTE(__nonnull__(1));

OG_MACRO_C_BLOCK_END
#endif

#include "Stream.h"
#include "InlineFunctions.h"

struct OgExceptionCollectionIoException OgIoStreamMemoryStreamCreate(
    struct OgIoStream *const pStreamOutput,
    struct OgAllocator *const paAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemoryStreamFlag iemsfFlag
);
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamFlush(
    struct OgIoStream *const pisStream, OgBoolean bCleanBuffer
)
{
    struct OgExceptionCollectionIoException e = {};
    return e;
}
OgConstantString OgIoStreamMemoryStreamGetStreamType(
    void
)
{
    return ("OpenStg.Base.IO.MemoryStream");
}
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWriteBinary(
    struct OgIoStream *pisStream,
    const OgByte *const pbSource,
    OgUnsignedInteger64 uBytesToWrite,
    OgBoolean *const pbEndOfFile
);
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamWrite(
    struct OgIoStream *pisStream,
    OgConstantString pcsSource,
    OgSignedInteger64 iCharatcterToWrite,
    OgBoolean *const pbEndOfFile
);
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamReadBinary(
    struct OgIoStream *const pisStream,
    OgByte *const pbBuffer,
    OgUnsignedInteger64 uBufferSize,
    OgUnsignedInteger64 uBytesToRead,
    OgUnsignedInteger64 *const puBytesRead,
    OgBoolean *const pbEndOfFile
);
struct OgExceptionCollectionIoException OgIoStreamMemoryStreamRead(
    struct OgIoStream *const pisStream,
    OgCharacter *const psDestinationBuffer,
    OgUnsignedInteger64 uDestinationBufferSize,
    OgUnsignedInteger64 uBufferSize,
    OgBoolean *const pbEndOfFile
);

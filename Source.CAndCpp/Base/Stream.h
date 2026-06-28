#include <OpenSTG/OpenStgBase.InputAndOutput.h>

OG_MACRO_EXPORT struct OgIoStream OgIoStreamCreateMemeryStream(
    struct OgAllocator *const pAllocator,
    OgSignedInteger64 iAlignment,
    OgUnsignedInteger64 uBufferSize,
    enum OgIoEnumMemeryStreamFlag iemsfFlag);

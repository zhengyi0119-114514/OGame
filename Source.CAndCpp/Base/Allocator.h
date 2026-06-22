#include <OpenSTG/OpenStgBase.h>

#if !defined(OPEN_STG_ALLOCATOR_H)
#define OPEN_STG_ALLOCATOR_H 1
OG_MACRO_C_BLOCK_BEGIN

OG_MACRO_EXPORT OgException OgAllocatorCheckBasic(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);
OG_MACRO_EXPORT OgException OgAllocatorCheckSupportForAlignmentSupport(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);
OG_MACRO_EXPORT OgException OgAllocatorCheckSupportForResize(
    const struct OgAllocator *pAllocator,
    OgBoolean *pbResult);
OG_MACRO_EXPORT OgException OgAllocatorGetDefaultAllocator(struct OgAllocator *paOutputAllocator);
OG_MACRO_EXTERN OgAllocator OgAllocatorCreateCStandardAllocator();

OG_MACRO_C_BLOCK_END
#endif

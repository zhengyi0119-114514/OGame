#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_INLINE_H)
#define OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_INLINE_H
#include <OpenSTG/OpenStgBase.InputAndOutput.h>
OG_MACRO_C_BLOCK_BEGIN

inline struct OgExceptionCollectionIoException OgIoStreamFormatAndWriteText(
    OgIoStream *pisStream, OgUnsignedInteger64 uFormatFlag, OgConstantString pcsFormat, ...
)
{
    va_list ptrArgumentList;
    va_start(ptrArgumentList, pcsFormat);
    struct OgExceptionCollectionIoException e =
        OgIoStreamFormatAndWriteTextV(pisStream, uFormatFlag, pcsFormat, ptrArgumentList);
    va_end(ptrArgumentList);
    return e;
}

OG_MACRO_C_BLOCK_END
#endif

#if !defined(OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_INLINE_H)
#define OPEN_STG_MACRO_BASE_INPUT_AND_OUTPUT_INLINE_H
#include <OpenSTG/OpenStgBase.InputAndOutput.h>
OgMacroCBlockBegin

    OgMacroAlwaysInline inline struct OgExceptionCollectionIoException
    OgIoStreamFormatAndWriteText(
        OgIoStream *pisStream,
        OgUnsignedInteger64 uFormatFlag,
        OgConstantString pcsFormat,
        ...
    )
{
    va_list ptrArgumentList;
    va_start(ptrArgumentList, pcsFormat);
    struct OgExceptionCollectionIoException e =
        OgIoStreamFormatAndWriteTextV(pisStream, uFormatFlag, pcsFormat, ptrArgumentList);
    va_end(ptrArgumentList);
    return e;
}

OgMacroCBlockEnd
#endif

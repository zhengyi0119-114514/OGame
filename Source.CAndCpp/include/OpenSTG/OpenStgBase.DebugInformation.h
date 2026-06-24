#include <OpenSTG/OpenStgBase.Types.h>
#include <OpenSTG/OpenStgBase.Macro.h>
#include <OpenSTG/OpenStgBase.Exceptions.h>

#if !defined(OPEN_STG_MACRO_BASE_DEBUG_INFORMATION_H)
#define OPEN_STG_MACRO_BASE_DEBUG_INFORMATION_H 1
OG_MACRO_C_BLOCK_BEGIN

typedef struct OgDebugSource
{
    OgBoolean (*Initialize)(void);
    OgBoolean (*CleanUp)(void);
    OgException (*GetCallNumberOfStackFrame)(OgUnsignedIntegerSize *puStacks);
    OgException (*CreateCallStackFrames)(
        OgPVoid *apvFrames,
        OgUnsignedIntegerSize uMaxFrame,
        OgUnsignedIntegerSize *puFramesWritte);
    OgPVoid AdditionalData;
} OgDebugSource;

struct OgDebugSource *OgDebugGetSystemDebugSource(void);
struct OgDebugSource *OgDebugGetDefaultDebugSource(void);
OG_MACRO_EXTERN OgException OgDebugPrintHexadecimalContent(
    OgPVoid pvData,
    OgUnsignedIntegerSize uDataSize);


OG_MACRO_C_BLOCK_END
#endif

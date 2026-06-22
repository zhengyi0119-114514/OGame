#include <OpenSTG/OpenStgBase.h>
#if !defined OPEN_STG_EDT_H
#define OPEN_STG_EDT_H
OG_MACRO_C_BLOCK_BEGIN

typedef void *OgElectromagneticDotTimer;

OG_MACRO_EXPORT OgElectromagneticDotTimer *OgElectromagneticDotTimerCreate(int8_t iDotFrequency);
OG_MACRO_EXPORT void OgElectromagneticDotTimerDestory(OgElectromagneticDotTimer *pEdt);
OG_MACRO_EXPORT OgUnsignedInteger64 OgElectromagneticDotTimerPullTask(OgElectromagneticDotTimer *pEdt);
OG_MACRO_EXPORT void OgElectromagneticDotTimerSkipATimeStamp(OgElectromagneticDotTimer *pEdt);
OG_MACRO_EXPORT void OgRefreshElectromagneticDotTimer(OgElectromagneticDotTimer *pEdt);

OG_MACRO_C_BLOCK_END
#endif

#include <OpenStg/OpenStgDefine.h>

#if !defined OPEN_STG_GRAPHICS_PRIVATE_H
#define OPEN_STG_GRAPHICS_PRIVATE_H
#if defined __cplusplus
extern "C"
{
#endif
    OG_EXPORT BOOL_T OG_API OgGpInit();
    OG_EXPORT void OG_API OgGpQuit();
    OG_EXPORT void OG_API OgGpFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer);
#if defined __cplusplus
}
#endif
#endif
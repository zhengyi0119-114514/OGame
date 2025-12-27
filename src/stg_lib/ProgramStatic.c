#include "CloseStg.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#if defined _WIN32
#include <windows.h>
#endif
#if defined POSIX
#include <unistd.h>
#endif

OG_PRIVATE OG_PROGRAM_DATA_T *s_pdData = NULL;
OG_BOOL_T initProgramData(uint32_t uInternalModuleCount)
{
    s_pdData = (OG_PROGRAM_DATA_T *)malloc(sizeof(OG_PROGRAM_DATA_T));
    if (s_pdData == NULL)
    {
        setError(OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR);
        return OG_FALSE;
    }
    memset((void *)s_pdData, 0, sizeof(OG_PROGRAM_DATA_T));
    if (!initModuleContainer(uInternalModuleCount))
        return OG_FALSE;
    return OG_TRUE;
}
OG_PROGRAM_DATA_T *getProgramData()
{
    return s_pdData;
}
OG_BOOL_T freeProgramData()
{
    OG_BOOL_T bResult = TRUE;
    bResult &= freeModuleContainer();
    free(s_pdData);
    s_pdData = NULL;
    return bResult;
}
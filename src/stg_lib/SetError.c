#include "CloseStg.h"
#include <stddef.h>
#include <stdio.h>

#if __has_include("inttypes.h")
#include <inttypes.h>
#endif

void setErrorAndMessage(const char *pszFile, const char *pszFunction, uint32_t uLine, OG_ERROR_T eErrno,
                        const char *pszMessage)
{
    OG_ERRNO = eErrno;
    OG_ERROR_RECOVERABLE = TRUE;
#if defined DEBUG || defined _DEBUG
    snprintf(OG_ERROR_MESSAGE, OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH,
             "[%-20s]:%" PRIu32 ":%016" PRIX64 ":%s", pszFile, uLine, OG_ERRNO, pszMessage);
#else
    strcpy_s(OG_ERROR_MESSAGE, OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH, pszMessage);
#endif
}
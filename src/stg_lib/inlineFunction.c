#include "CloseStg.h"
#include <string.h>

void setCrRecoverableError(OG_ERROR_CODE_T ec)
{
    OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->ecErrno = OgCrMakeError(OPEN_STG_NAMESPACE_CORE, ec);
    ptlss->bIsRecoverableException = TRUE;
    ptlss->pszAdditionalErrorMessage[0] = '\0';
}
void OG_CDECL setCrIrreversibleError(OG_ERROR_CODE_T ec)
{
    OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->bIsRecoverableException = FALSE;
    ptlss->ecErrno = OgCrMakeError(OPEN_STG_NAMESPACE_CORE, ec);
    ptlss->pszAdditionalErrorMessage[0] = '\0';
}

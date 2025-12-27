#include "CloseStg.h"
#include <string.h>

void setError(OG_ERROR_CODE_T ec)
{
    OG_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgGetTLSStruct();
    ptlss->ecErrno = OgMakeError(OPEN_STG_NAMESPACE_CORE, ec);
    strcpy_s((void *)ptlss->pszAdditionalErrorMessage, OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH, "");
}

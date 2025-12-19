#include "CloseStg.h"

void setError(OG_ERROR_CODE ec)
{
    OgTHREAD_LOCAL_STORAGE_STRUCT *ptlss = OgGetTLSStruct();
    ptlss->ecErrno = OG_MAKE_ERROR(OG_ERROR_NAMESPACE_CORE, ec); 
    ptlss->pszErrorMessage = NULL;
}

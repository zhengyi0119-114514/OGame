#include "OpenStg/CloseStgCore.h"
#include <stdlib.h>
#include <string.h>

OG_PRIVATE OG_CR_PV_PROGRAM_STATIC_VARIABLES *s_var = NULL;
BOOL_T OG_API ogCrPvInitProgramStaticVariables(void)
{
    s_var = (OG_CR_PV_PROGRAM_STATIC_VARIABLES *)malloc(sizeof(OG_CR_PV_PROGRAM_STATIC_VARIABLES));
    if (s_var == NULL)
    {
        OgCrSetRecoverableError(OgCrMakeError(OPEN_STG_NAMESPACE_CORE, OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR));
        return FALSE;
    }
    memset((void *)s_var, 0, sizeof(OG_CR_PV_PROGRAM_STATIC_VARIABLES));
    return TRUE;
}
OG_CR_PV_PROGRAM_STATIC_VARIABLES *OG_API ogCrPvGetProgramStaticVariables(void)
{
    return s_var;
}
void OG_API ogCrPvFreeProgramStaticVariables(void)
{
    free(s_var);
    s_var = NULL;
}
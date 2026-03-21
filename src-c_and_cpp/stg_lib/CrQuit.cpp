#include "OpenStg/CloseStgCore.h"

BOOL_T OG_API OgCrQuit()
{
    OgCrDestoryProgramModule();
    return TRUE;
}
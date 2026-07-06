#include "Exception.h"
#include <stdio.h>


OG_MACRO_PRIVATE OgConstantString OgExceptionStructureOutOfRangeGetExceptionName()
{
    return ("OpenStg.Base.Exception.OutOfRangeException");
}
OG_MACRO_EXTERN struct OgExceptionInformation *OgExceptionStructureOutOfRangeGetInformation(void);

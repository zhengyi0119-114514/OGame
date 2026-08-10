#include "Exception.h"

#if defined (_WIN32)
#include <Windows.h>
#else
#include <execinfo.h>
#include <stdlib.h>
#endif

OgMacroNoreturn void OgExceptionPanic(OgConstantString pcsDescription)
{
#if defined (_WIN32)
#else
    exit(EXIT_FAILURE);   
#endif
}

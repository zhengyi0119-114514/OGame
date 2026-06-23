#include "Exception.h"

#if defined (_WIN32)
#include <Windows.h>
#else
#include <execinfo.h>
#include <stdlib.h>
#endif

OG_MACRO_NORETURN void OgExceptionPanic(OgException e)
{
#if defined (_WIN32)
#else
    exit(EXIT_FAILURE);   
#endif
}

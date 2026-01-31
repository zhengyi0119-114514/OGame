#include "CloseStgNetwork.h"

#if defined __unix || defined __unix__
#include <sys/socket.h>
#endif
#if OPEN_STG_MACRO_IS_WINDOWS
#endif

BOOL_T OG_API OgNwInit()
{
#if OPEN_STG_MACRO_IS_WINDOWS

#endif
return TRUE;
}
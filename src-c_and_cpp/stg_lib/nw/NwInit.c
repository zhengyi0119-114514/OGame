#include "OpenStg/CloseStgNetwork.h"
#include <OpenStg/OpenStgCore.h>

#if defined __unix || defined __unix__
#include <sys/socket.h>
#endif
#if OPEN_STG_MACRO_IS_WINDOWS
#include <winsock2.h>
#endif

BOOL_T OG_API OgNwInit()
{
#if OPEN_STG_MACRO_IS_WINDOWS
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        OgCrSetIrreversibleError(OgCrMakeError(OPEN_STG_NAMESPACE_NETWORK, OPEN_STG_ERRPR_MESSAGE_NETWORK_INIT_FAILED));
    }
#endif
    return TRUE;
}

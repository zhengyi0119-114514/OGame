#include "CloseStg.h"
#include "string.h"

void OgCrGetErrorMessage(OG_ERROR_CODE code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    switch (code)
    {
    case OPEN_STG_ERROR_MESSAGE_NO_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "No error.");
    }
    case OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer,
                 "Memory alloc failed."
                 "This is usually caused by insufficient memory.");
    }
    case OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Invalid parameter.");
    }
    case OPEN_STG_ERROR_MESSAGE_MODULE_EXIST: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module exist");
    }
    case OPEN_STG_ERROR_MESSAGE_NOT_INITIALIZED: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module is not initalized.");
    }
    }
}
void OgSdlGetErrorMessage(OG_ERROR_CODE code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    strcpy_s(pszBuffer, uLengthOfBuffer, OgGetTLSStruct()->pszAdditionalErrorMessage);
}
void OgGetErrorMessage(OG_ERROR eError, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    OG_ERROR_NAMESPACE ns = OgGetErrorNamespace(eError);
    getProgramData()->rgModules[ns].pmModule.pfGetErrorMessage(OgGetErrorCode(eError), pszBuffer, uLengthOfBuffer);
}

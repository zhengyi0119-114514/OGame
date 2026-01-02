#include "CloseStg.h"
#include <string.h>

void OgCrFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    switch (code)
    {
    case OPEN_STG_ERROR_MESSAGE_NO_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "No error.");
    }
    break;
    case OPEN_STG_ERROR_MESSAGE_MEMORY_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer,
                 "Memory alloc failed."
                 "This is usually caused by insufficient memory.");
    }
    break;
    case OPEN_STG_ERROR_MESSAGE_INVALID_PARAMETER: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Invalid parameter.");
    }
    break;
    case OPEN_STG_ERROR_MESSAGE_MODULE_EXIST: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module exist");
    }
    break;
    case OPEN_STG_ERROR_MESSAGE_NOT_INITIALIZED: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module is not initalized.");
    }
    break;
    case OPEN_STG_ERROR_MESSAGE_UNDEFINED_MEMORY_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Undefined behavior caused by memory allocation errors");
    }
    break;
    }
}
void OgSdlFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    strcpy_s(pszBuffer, uLengthOfBuffer, OgCrGetTLSStruct()->pszAdditionalErrorMessage);
}

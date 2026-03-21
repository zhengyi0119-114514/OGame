#include "OpenStg/CloseStgCore.h"
#include <string.h>

void OgCrFormatErrorMessage(OG_ERROR_CODE_T code, char *pszBuffer, uint64_t uLengthOfBuffer)
{
    switch (code)
    {
    case OPEN_STG_ERROR_CODE_CORE_UNKNOWN_EXCEPTION: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "No error.");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_MEMORY_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer,
                 "Memory alloc failed."
                 "This is usually caused by insufficient memory.");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_INVALID_PARAMETER: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Invalid parameter.");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_MODULE_EXIST: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module exist.");
    }
    case OPEN_STG_ERROR_CODE_CORE_MODULE_NOT_EXIST: {
        strcpy_s(pszBuffer,uLengthOfBuffer,"Module not exist.");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_NOT_INITIALIZED: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Module is not initalized.");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_UNDEFINED_MEMORY_ERROR: {
        strcpy_s(pszBuffer, uLengthOfBuffer, "Undefined behavior caused by memory allocation errors");
    }
    break;
    case OPEN_STG_ERROR_CODE_CORE_OUT_OF_RANGE:{
        strcpy_s(pszBuffer,uLengthOfBuffer, "Out of range");
    }
    break;
    }
}

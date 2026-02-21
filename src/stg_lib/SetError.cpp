#define FMT_UNICODE 1
#include "OpenStg/CloseStgCore.h"
#include <assert.h>
#include <fmt/format.h>
#include <fmt/printf.h>
#include <fmt/xchar.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#if __has_include("inttypes.h")
#include <inttypes.h>
#endif

#if OPEN_STG_MACRO_IS_WINDOWS
#include <windows.h>
#include <dbghelp.h>
#endif

#if defined __unix__ || defined __unix
#include <execinfo.h>
#include <unistd.h>
#endif

#define MAX_FRAMES 96
#define MAX_NAME_LEN 128
OG_INTERNAL void OG_API ogCrInvokeErrorHandlerFunction();
void OG_API ogCrInvokeErrorHandlerFunction()
{
    OG_CR_EXCEPTION_HANDLER_FUNCTION_T *funcs = ogCrPvGetProgramStaticVariables()->rgfnExceptionHandlers;
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    OG_CR_EXCEPTION_HANDLER_STATUS ehs{};
    for (size_t uIndex = 0; uIndex < OPEN_STG_CONST_MAX_EXCEPTION_HANDLER_FUNCTION; uIndex++)
    {
        if (funcs[uIndex] != NULL)
        {
            ehs = funcs[uIndex](ptlss->ecErrno, ptlss->bIsRecoverableException);
        }
    }
}
void OG_API OgCrSetErrorHandler(OG_CR_EXCEPTION_HANDLER_FUNCTION_T pfnHandler)
{
}
void OG_API OgCrSetRecoverableError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->ecErrno = e;
    ptlss->szAdditionalErrorMessage[0] = '\0';
    ptlss->bIsRecoverableException = TRUE;
    ogCrInvokeErrorHandlerFunction();
}
void OG_API OgCrSetIrreversibleError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->szAdditionalErrorMessage[0] = '\0';
    ptlss->bIsRecoverableException = FALSE;
    ptlss->ecErrno = e;
    ogCrInvokeErrorHandlerFunction();
    _Exit(EXIT_FAILURE);
}
#if OPEN_STG_MACRO_IS_DEBUG
inline void OG_API OG_ALWAYS_INLINE ogCrPrintException(const char *pszExpression, const char *pszFunction,
                                                       const char *pszFile, const char *pszEexceptionMessage,
                                                       OG_ERROR_T uError, uint64_t uLine)
{
    fmt::fprintf(stderr, "[%s:%" PRId64 "]%s|%016" PRIx64 "|%s|%s\n", pszFile, uLine, pszFunction, uError,
                 pszExpression, pszEexceptionMessage);
}
#endif
void *OG_API OgCrNoExceptPtrVa(void *p)
{
    if (p == NULL)
    {
        if (OgCrGetErrorNamesoace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
        {
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        else
        {
            OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        fmt::fprintf(stderr, "exception:%016" PRIx64 "\n", OG_ERRNO);
        OgCrSetIrreversibleError(OG_ERRNO);
    }
    else
    {
        return p;
    }
}
void *OG_API OgCrNoExceptPtrEx(void *p, const char *pszExpression, const char *pszFunction, const char *pszFile,
                               uint64_t uLine)
{
    if (p == NULL)
    {
        if (OgCrGetErrorNamesoace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
        {
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        else
        {
            OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        ogCrPrintException(pszExpression, pszFunction, pszFile, OG_CHAR_BUFFER, OG_ERRNO, uLine);
        OgCrSetIrreversibleError(OG_ERRNO);
    }
    return p;
}
BOOL_T OG_API OgCrNoExceptBooleanVa(BOOL_T b)
{
    if (!b)
    {
        OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        fmt::fprintf(stderr, "exception:%s\n", OG_CHAR_BUFFER);
    }
    return b;
}
BOOL_T OG_API OgCrNoExceptBooleanEx(BOOL_T b, const char *pszExpression, const char *pszFunction, const char *pszFile,
                                    uint64_t uLine)
{
    if (!b)
    {
        if (OgCrGetErrorNamesoace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
        {
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        else
        {
            OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        ogCrPrintException(pszExpression, pszFunction, pszFile, OG_CHAR_BUFFER, OG_ERRNO, uLine);
        OgCrSetIrreversibleError(OG_ERRNO);
    }
    return b;
}
void OG_API OgCrPrintStackTrace()
{
    fputs("Stack trace:\n", stderr);
#if OPEN_STG_MACRO_IS_WINDOWS
    HANDLE hCurrentProcess = NULL;
    DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), &hCurrentProcess, 0, FALSE,
                    DUPLICATE_SAME_ACCESS);
    SymInitialize(hCurrentProcess, NULL, TRUE);
    PVOID rgpvBuffer[MAX_FRAMES];
    WORD wFrames = CaptureStackBackTrace(0, MAX_FRAMES, rgpvBuffer, NULL);
    size_t sSymbolInfoSize = sizeof(SYMBOL_INFOW) + sizeof(WCHAR) * MAX_NAME_LEN;
    PSYMBOL_INFOW psi = (PSYMBOL_INFOW)malloc(sSymbolInfoSize);
    ZeroMemory((PVOID)psi, sSymbolInfoSize);
    psi->MaxNameLen = MAX_NAME_LEN;
    for (WORD wIndex = 0; wIndex < wFrames; wIndex++)
    {
        if (SymFromAddrW(hCurrentProcess, (DWORD64)rgpvBuffer[wIndex], 0, psi))
        {
            fwprintf(stderr, L"\t%" PRId16 "(%16" PRIx64 "):%s\n", (uint16_t)wIndex, psi->Address, psi->Name);
        }
        else
        {
            fmt::fprintf(stderr, "\t%" PRId16 "(%p):???\n", (uint16_t)wIndex, rgpvBuffer[wIndex]);
        }
    }
    SymCleanup(hCurrentProcess);
    CloseHandle(hCurrentProcess);
#elif defined __unix__
    void *rgpvBuffers[MAX_FRAMES];
    int iNumberOfFrames = backtrace(rgpvBuffers, MAX_FRAMES);
    char **rgpszSymbols = backtrace_symbols(rgpvBuffers, iNumberOfFrames);
    for (int iIndex = 0; iIndex < iNumberOfFrames; iIndex++)
    {
        fmt::fprintf(stderr, "\t%d:%s\n", iIndex + 1, rgpszSymbols[iIndex]);
    }
    free(rgpszSymbols);
#endif
}

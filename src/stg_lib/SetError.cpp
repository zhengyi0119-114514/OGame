#include "CloseStgCore.h"
#include <fmt/format.h>
#include <fmt/printf.h>
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
#define MAX_EXCEPTION_HANDLER 16
void OG_API ogCrPvDefaultExceptionHandler(OG_ERROR_T e)
{
    OgFormatErrorMessage(e, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
    fmt::fprintf(stderr, "%016" PRIx64 ":%s\n", OG_CHAR_BUFFER);
    OgCrPrintStackTrace();
}
OG_CR_EXCEPTION_HANDLER_FUNCTION_T s_pfnHandler = NULL;
void OG_API OgCrSetErrorHandler(OG_CR_EXCEPTION_HANDLER_FUNCTION_T pfnHandler)
{
    s_pfnHandler = pfnHandler;
}
void OG_API OgCrSetRecoverableError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->ecErrno = e;
    ptlss->bIsRecoverableException = TRUE;
    if (s_pfnHandler != NULL)
    {
        s_pfnHandler(OG_ERRNO);
    }
}
void OG_API OgCrSetIrreversibleError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->bIsRecoverableException = FALSE;
    ptlss->ecErrno = e;
    if (s_pfnHandler != NULL)
    {
        s_pfnHandler(OG_ERRNO);
    }
    _Exit(EXIT_FAILURE);
}
#if OPEN_STG_MACRO_IS_DEBUG
inline void OG_API OG_ALWAYS_INLINE ogCrPrintException(const char *pszExpression, const char *pszFunction,
                                                       const char *pszFile, const char *pszEexceptionMessage,
                                                       OG_ERROR_T uError, uint64_t uLine)
{
    fmt::fprintf(stderr, "[%s:%" PRId64 "]%s|%016" PRIx64 "|%s|%s\n", pszFile, (signed long long int)uLine, pszFunction,
                 uError, pszExpression, pszEexceptionMessage);
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
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER,
                                   OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
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
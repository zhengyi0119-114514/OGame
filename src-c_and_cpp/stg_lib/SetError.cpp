#define FMT_UNICODE 1
#include "OpenStg/CloseStgCore.h"
#include "OpenStgAllocator.hh"
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
#include <psapi.h>
#if OPEN_STG_MACRO_USE_LIBDWARF
#include <regex>
#include <libdwarf.h>
#include <libdwarf-2/dwarf.h>
#include <libdwarf-2/libdwarf.h>
#endif
#endif

#if defined __unix__ || defined __unix
#include <execinfo.h>
#include <unistd.h>
#endif

#define MAX_FRAMES 96
#define MAX_NAME_LEN 128
#define MAX_MODULE 128

OG_INTERNAL void OG_API ogCrPvInvokeErrorHandlerFunction();
void OG_API ogCrPvInvokeErrorHandlerFunction()
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
    OG_CR_EXCEPTION_HANDLER_FUNCTION_T *pfnHandlers = ogCrPvGetProgramStaticVariables()->rgfnExceptionHandlers;
    for (uint64_t uIndex = 0; uIndex < OPEN_STG_CONST_MAX_EXCEPTION_HANDLER_FUNCTION; uIndex++)
    {
        if (pfnHandlers[uIndex] == NULL)
        {
            pfnHandlers[uIndex] = pfnHandler;
            return;
        }
    }
    return;
}
void OG_API OgCrSetRecoverableErrorAndMessage(OG_ERROR_T ec, const char *pszMessage)
{
    auto &reftlss = *OgCrGetTLSStruct();
    reftlss.bIsRecoverableException = TRUE;
    reftlss.ecErrno = ec;
    strcpy_s(reftlss.szAdditionalErrorMessage, OPEN_STG_CONST_ADDITIONAL_ERROR_MESSAGE_STRING_LENGTH, pszMessage);
    ogCrPvInvokeErrorHandlerFunction();
}
void OG_API OgCrSetRecoverableError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->ecErrno = e;
    ptlss->szAdditionalErrorMessage[0] = '\0';
    ptlss->bIsRecoverableException = TRUE;
    ogCrPvInvokeErrorHandlerFunction();
}
void OG_API OgCrSetIrreversibleError(OG_ERROR_T e)
{
    OG_CR_THREAD_LOCAL_STORAGE_STRUCT *ptlss = OgCrGetTLSStruct();
    ptlss->szAdditionalErrorMessage[0] = '\0';
    ptlss->bIsRecoverableException = FALSE;
    ptlss->ecErrno = e;
    ogCrPvInvokeErrorHandlerFunction();
    _Exit(EXIT_FAILURE);
}
#if OPEN_STG_MACRO_IS_DEBUG
inline void OG_API OG_ALWAYS_INLINE ogCrPvPrintException(const char *pszExpression, const char *pszFunction,
                                                         const char *pszFile, const char *pszEexceptionMessage,
                                                         OG_ERROR_T uError, uint64_t uLine)
{
    fmt::fprintf(stderr, "[%s:%" PRId64 "]%s|%016" PRIx64 "|%s|%s\n", pszFile, uLine, pszFunction, uError,
                 pszExpression, pszEexceptionMessage);
}
#else
#define ogCrPvPrintException(e, fun, file, msg, ec, l)                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
    } while (1);
#endif

void *OG_API OgCrNoExceptPtrVa(void *p)
{
    if (p == NULL)
    {
        if (OgCrGetErrorNamespace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
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
        if (OgCrGetErrorNamespace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
        {
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        else
        {
            OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        ogCrPvPrintException(pszExpression, pszFunction, pszFile, OG_CHAR_BUFFER, OG_ERRNO, uLine);
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
        OgCrSetIrreversibleError(OG_ERRNO);
    }
    return b;
}
BOOL_T OG_API OgCrNoExceptBooleanEx(BOOL_T b, const char *pszExpression, const char *pszFunction, const char *pszFile,
                                    uint64_t uLine)
{
    if (!b)
    {
        if (OgCrGetErrorNamespace(OG_ERRNO) == OPEN_STG_NAMESPACE_CORE)
        {
            OgCrFormatErrorMessage(OgCrGetErrorCode(OG_ERRNO), OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        else
        {
            OgFormatErrorMessage(OG_ERRNO, OG_CHAR_BUFFER, OPEN_STG_CONST_CHAR_BUFFER_LENGTH);
        }
        ogCrPvPrintException(pszExpression, pszFunction, pszFile, OG_CHAR_BUFFER, OG_ERRNO, uLine);
        OgCrSetIrreversibleError(OG_ERRNO);
    }
    return b;
}
#if OPEN_STG_MACRO_USE_LIBDWARF
OG_INTERNAL void OG_API ogCrPvInitExceptionModule(void)
{
    HMODULE rgModules[MAX_MODULE * 4];
    char szBuffer[_MAX_PATH];
    auto &refStaticVariables = *ogCrPvGetProgramStaticVariables();
    auto *prgDbgs = new std::vector<std::shared_ptr<OG_CR_PV_DBG_INFO>>();
    refStaticVariables.rgpDbg = (void *)prgDbgs;
    DWORD dwNeeded = 0;
    ZeroMemory((void *)rgModules, sizeof(rgModules));
    ZeroMemory((void *)szBuffer, sizeof(szBuffer));
    std::regex systemDynamicLinkLibraryRegex(
        R"==(((^[A-Z]{1}:\\[Ww][Ii][Nn][Dd][Oo][Ww][Ss])|(^.*((ntdll)|(kernel32)|(kernelbase)|(msvcrt)|(ucrtbase)|)=="
        R"==((user32)|(gdi32)|(gdiplus)|(uxtheme)|(dwmapi)|(ws2_32)|(winhttp)|(wininet)|(dnsapi)|(iphlpapi)|(advapi32)|)=="
        R"==((sechost)|(crypt32)|(bcrypt)|(ole32)|(oleaut32)|(shell32)|(shlwapi)|(version)|(setupapi)))\.dll$)==");
    Dwarf_Error e = 0;
    if (EnumProcessModules(GetCurrentProcess(), rgModules, (DWORD)sizeof(rgModules), &dwNeeded))
    {
        for (DWORD dwIndex = 0; dwIndex < dwNeeded; dwIndex++)
        {
            if (GetModuleFileNameExA(GetCurrentProcess(), rgModules[dwIndex], szBuffer, _MAX_PATH) and
                (not std::regex_match(szBuffer, systemDynamicLinkLibraryRegex)))
            {
                size_t sFilePath = strlen(szBuffer) + 1;
                size_t sDbgInfo = sizeof(OG_CR_PV_DBG_INFO) + sFilePath;
                OG_CR_PV_DBG_INFO *pInfo = NULL;
                if ((pInfo = (OG_CR_PV_DBG_INFO *)malloc(sDbgInfo)) == NULL)
                {
                    continue;
                }
                ZeroMemory((void *)pInfo, sDbgInfo);
                auto ptr = std::shared_ptr<OG_CR_PV_DBG_INFO>(
                    pInfo,
                    [](OG_CR_PV_DBG_INFO *p) {
                        dwarf_finish(static_cast<Dwarf_Debug>(p->dbg));
                        free(p);
                    });
                Dwarf_Debug &refdbg = *((Dwarf_Debug *)&pInfo->dbg);
                if (pInfo == NULL)
                {
                    return;
                }
                if (dwarf_init_path(szBuffer, NULL, 0, DW_GROUPNUMBER_ANY, NULL, NULL, &refdbg, &e) == DW_DLV_OK)
                {
                    strcpy_s(pInfo->szFilePath, sFilePath, szBuffer);
                    prgDbgs->push_back(ptr);
                }
            }
        }
    }
}
OG_INTERNAL void OG_API ogCrPvQuitExceptionModule(void *)
{
    auto rgpDbg =
        static_cast<std::vector<std::shared_ptr<OG_CR_PV_DBG_INFO>> *>(ogCrPvGetProgramStaticVariables()->rgpDbg);
    operator delete(rgpDbg);
}
#else
OG_INTERNAL void OG_API ogCrPvInitExceptionModule(void)
{
}
OG_INTERNAL void OG_API ogCrQuitExceptionModule(void)
{
}
#endif
#if OPEN_STG_MACRO_USE_LIBDWARF
OG_INTERNAL BOOL_T OG_API ogCrPvInRange(Dwarf_Debug dbg, Dwarf_Die die, Dwarf_Addr addr)
{
    Dwarf_Error e = 0;
    Dwarf_Addr adLow = NULL, adHight = NULL;
    if ((dwarf_lowpc(die, &adLow, &e) == DW_DLV_OK) && (dwarf_highpc_b(die, &adHight, NULL, NULL, &e) == DW_DLV_OK))
    {
        return FALSE;
    }
    return (adLow <= addr) && (addr < adHight);
}
OG_INTERNAL BOOL_T OG_API ogCrPvLookupFunctionAtDwarfTable(Dwarf_Addr daAddr, char *pszFunctionName,
                                                           uint32_t uFunctionNameBufferLength, char *pszSourcePath,
                                                           uint32_t uSourcePathBufferLength, uint32_t *puLine)
{
    Dwarf_Error e = NULL;
    auto &rgpDbg =
        *static_cast<std::vector<std::shared_ptr<OG_CR_PV_DBG_INFO>> *>(ogCrPvGetProgramStaticVariables()->rgpDbg);
    for (const auto &pInfo : rgpDbg)
    {
        Dwarf_Debug dbg = static_cast<Dwarf_Debug>(pInfo->dbg);
        Dwarf_Unsigned uNextCuHeader, uHeaderLength = 0;
        Dwarf_Half hAddresuSize = 0, hVersionStamp = 0, hLengthSize = 0, hExtensionSize = 0, hCurrentCuType = 0;
        Dwarf_Off ofAbbrevOffset = 0;

        while (dwarf_next_cu_header_d(dbg, NULL, &uHeaderLength, &hVersionStamp, &ofAbbrevOffset, &hAddresuSize,
                                      &hLengthSize, &hExtensionSize, NULL, NULL, &uNextCuHeader, &hCurrentCuType,
                                      &e) == DW_DLV_OK)
        {
            Dwarf_Die die = 0;
            if (!(dwarf_siblingof_b(dbg, die, false, &die, &e) == DW_DLV_OK))
            {
                continue;
            }
            Dwarf_Half hTag = 0;
            if (dwarf_tag(die, &hTag, &e) != DW_DLV_OK)
            {
                continue;
            }
            if (!(hTag == DW_TAG_subrange_type && ogCrPvInRange(dbg, die, daAddr)))
            {
                continue;
            }
            Dwarf_Attribute a = NULL;
            char *pszBuffer = NULL;
            if (uFunctionNameBufferLength > 0 && pszFunctionName != NULL)
            {
                // 获取Name
                pszFunctionName[0] = '\0';
                if (dwarf_attr(die, DW_AT_name, &a, &e) == DW_DLV_OK)
                {
                    if (dwarf_formstring(a, &pszBuffer, &e) == DW_DLV_OK)
                    {
                        strcpy_s(pszFunctionName, uFunctionNameBufferLength, pszBuffer);
                        dwarf_dealloc(dbg, (void *)pszBuffer, DW_DLA_STRING);
                        pszBuffer = NULL;
                    }
                    dwarf_dealloc(dbg, (void *)a, DW_DLA_ATTR);
                    a = NULL;
                }
                else if ((dwarf_attr(die, DW_AT_linkage_name, &a, &e)) == DW_DLV_OK) // 找不到Name，尝试获取LinkName
                {
                    if (dwarf_formstring(a, &pszBuffer, &e) == DW_DLV_OK)
                    {
                        strcpy_s(pszFunctionName, uFunctionNameBufferLength, pszBuffer);
                        dwarf_dealloc(dbg, (void *)pszBuffer, DW_DLA_STRING);
                        pszBuffer = NULL;
                    }
                    dwarf_dealloc(dbg, (void *)a, DW_DLA_STRING);
                    a = NULL;
                }
                else
                {
                    strcpy_s(pszFunctionName, uFunctionNameBufferLength, "<\?\?\?-Unknown>");
                }
            }
            if (uSourcePathBufferLength && pszSourcePath != NULL)
            {
                pszSourcePath[0] = '\0';
                if (dwarf_attr(die, DW_AT_decl_file, &a, &e) == DW_DLV_OK)
                {
                    if (dwarf_formstring(a, &pszBuffer, &e) == DW_DLV_OK)
                    {
                        strcpy_s(pszSourcePath, uSourcePathBufferLength, pszBuffer);
                        dwarf_dealloc(dbg, (void *)a, DW_DLA_STRING);
                        pszBuffer = NULL;
                    }
                    dwarf_dealloc(dbg, (void *)a, DW_DLA_ATTR);
                    a = NULL;
                }
            }
            if (puLine != NULL)
            {
                *puLine = 0;
                Dwarf_Unsigned uLine = 0;
                if (dwarf_attr(die, DW_AT_decl_line, &a, &e) == DW_DLV_OK)
                {
                    if (dwarf_formudata(a, &uLine, &e) == DW_DLV_OK)
                    {
                        (*puLine) = uLine;
                    }
                    dwarf_dealloc(dbg, (void *)a, DW_DLA_ATTR);
                    a = NULL;
                }
            }

            dwarf_dealloc(dbg, (void *)die, DW_DLA_DIE);
            return TRUE;
        }
    }
    return FALSE;
}
#endif
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
#if OPEN_STG_MACRO_USE_LIBDWARF
    char szFunctionName[MAX_NAME_LEN]{0};
    char szSourceFilePath[_MAX_PATH]{0};
    uint32_t uLine = 0;
    BOOL_T bDwarfReady = false;
#endif
    {
        size_t sSymbolInfoSize = sizeof(SYMBOL_INFOW) + sizeof(WCHAR) * MAX_NAME_LEN;
        PSYMBOL_INFOW psi = (PSYMBOL_INFOW)malloc(sSymbolInfoSize);
        ZeroMemory((PVOID)psi, sSymbolInfoSize);
        psi->MaxNameLen = MAX_NAME_LEN;
        for (WORD wIndex = 0; wIndex < wFrames; wIndex++)
        {
            if (SymFromAddrW(hCurrentProcess, (DWORD64)rgpvBuffer[wIndex], 0, psi))
            {
                fwprintf(stderr, L"\t(PDB)%" PRId16 "(%016" PRIx64 "):%s\n", (uint16_t)wIndex, (uint64_t)psi->Address,
                         psi->Name);
            }
#if OPEN_STG_MACRO_USE_LIBDWARF
            else if (bDwarfReady && ogCrPvLookupFunctionAtDwarfTable((Dwarf_Addr)rgpvBuffer[wIndex], szFunctionName,
                                                                     MAX_NAME_LEN, szSourceFilePath, _MAX_PATH, &uLine))
            {
                fmt::fprintf(stderr, "\t(DWARF)%" PRId16 "(%16" PRIx64 "):%s:%s\n", (uint16_t)wIndex,
                             (uint64_t)rgpvBuffer[wIndex], szSourceFilePath, szFunctionName);
            }
#endif
            else
            {
                fmt::fprintf(stderr, "\t%" PRId16 "(%p):???\n", (uint16_t)wIndex, rgpvBuffer[wIndex]);
            }
        }
    }
    SymCleanup(hCurrentProcess);
    CloseHandle(hCurrentProcess);
#if DWARF_FOUND
    fputs("DWARF", stderr);

#endif
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

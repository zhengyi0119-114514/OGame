#include "og.hpp"
#include <stdlib.h>
#if __has_include("windows.h")
#include <windows.h>
#endif
namespace open_stg
{
[[noreturn]]
void ExitProgram()
{
#ifdef WIN32
    ExitProcess(EXIT_SUCCESS);
#else
    _Exit(EXIT_SUCCESS);
#endif
}
} // namespace open_stg
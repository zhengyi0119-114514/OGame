#include "og_module.hpp"
#include "og_opt_h.hpp"
#include "og_view.hpp"
#include <list>
#ifndef OG_STGLIB_MAIN_H
#define OG_STGLIB_MAIN_H 1
namespace OpenGame
{
void InitOpenGame();
void QuitOpenGame();
[[noreturn]] void ExitProgram();
enum class ProgramOptions
{
    NONE = 0x0,
    RESIZABLE = 0x1,
};

class Program
{
    void EnterMainLoop();
};

} // namespace OpenGame
#endif

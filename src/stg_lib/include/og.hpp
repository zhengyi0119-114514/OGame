/**
 * @file open_game.hpp
 * @author IceThorn
 * @brief
 * @date 2025-07-19
 *
 * @copyright :(
 *
 */
#ifndef OGAME_STGLIB_H
#define OGAME_STGLIB_H 1

#include "og_error_h.hpp"
#include "og_interface.hpp"
#include "og_math_h.hpp"
#include "og_module.hpp"
#include "og_module_view_h.hpp"
#include "og_opt_h.hpp"
#include "og_sdl3_h.hpp"
#include "og_stg_h.hpp"
#include "og_task_h.hpp"
#include "og_templates_h.hpp"
#include "og_view.hpp"

namespace open_stg
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
  protected:
    std::shared_ptr<view_h::WindowScreen> m_spWindowScreen;
    std::shared_ptr<mod_h::GameScreen> m_spGameScreen;
    sdl3_h::SharedPtrRenderer m_spRenderer;
    StandardClock m_c{};

  public:
    ObjectPool<sdl3_h::SharedPtrSurface> SurfacePool{};
    ObjectPool<sdl3_h::SharedPtrTtfFont> TtfFontPool{};
    virtual void EnterMainLoop() = 0;
};
} // namespace open_stg
#endif // !OGAME_STGLIB_H

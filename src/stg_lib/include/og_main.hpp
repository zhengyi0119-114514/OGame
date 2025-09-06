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

CLASS Program
{
  protected:
    std::shared_ptr<View::WindowScreen> m_spWindowScreen;
    std::shared_ptr<Module::GameScreen> m_spGameScreen;
    sdl3_h::SharedPtrRenderer m_spRenderer;
    StandardClock m_c{};

  public:
    Program(sdl3_h::SharedPtrRenderer sprRenderer);
    Option::SurfacePool SurfacePool{};
    Option::TexturePool TexturePool{};
    Option::TtfFontPool TtfFontPool{};

    Void EnterMainLoop();
};
template <typename TGameObject>
concept CGameObject = requires(const TGameObject &co, TGameObject o) {
    { o.DoOperator() } -> std::same_as<void>;
} && std::movable<TGameObject> && std::copyable<TGameObject> && std::destructible<TGameObject>;
} // namespace OpenGame
#endif
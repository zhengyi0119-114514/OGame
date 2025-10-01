/**
 * @file og_module.hpp
 * @author ice-THORN
 * @brief [MVVM的模型部分]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-06
 *
 *
 */
#ifndef OGAME_STGLIB_MOUDLE_H
#define OGAME_STGLIB_MOUDLE_H 1
#include "og_math_h.hpp"
#include <SDL3/SDL.h>

namespace OpenGame::Module
{
class GameScreen
{
  protected:
  public:
    virtual ~GameScreen() noexcept = default;
    virtual void StartGame() = 0;
    virtual void StopGame() = 0;
    virtual void PauseGame() = 0;
    virtual void ContinueGame() = 0;
    virtual void HandleEvent(const SDL_Event &e, SDL_WindowID wid = 0);
    virtual void DoOperator() = 0;
    virtual Math::Size<int> GetScreenSize() const = 0;
};
} // namespace OpenGame::Module
#endif
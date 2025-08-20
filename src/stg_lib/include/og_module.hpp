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

namespace open_stg::mod_h
{
struct IGameObject
{
    virtual void DoOperator() = 0;
    
    virtual ~IGameObject() noexcept = default;
};
class GameScreen
{
  protected:
  public:
    virtual ~GameScreen() noexcept = default;
    virtual void StartGame() = 0;
    virtual void StopGame() = 0;
    virtual void PauseGame() = 0;
    virtual void ContinueGame() = 0;
    virtual void HandleEvent(const SDL_Event &e);
    virtual math_h::Size GetScreenSize() const = 0;
};
} // namespace open_stg::mod_h
#endif
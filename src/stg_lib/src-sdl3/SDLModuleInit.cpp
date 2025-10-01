#include "og.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <spdlog/spdlog.h>
namespace OpenGame::SDL3
{
void InitSdlModule()
{
#if defined DEBUG || defined _DEBUG
    SPDLOG_INFO("SDL Module init start.");
#endif
    if (not SDL_Init(SDL_INIT_VIDEO   // 图形
                  | SDL_INIT_AUDIO // 音频
                  // | SDL_INIT_JOYSTICK // 操纵杆
                  | SDL_INIT_HAPTIC  // 触屏
                  | SDL_INIT_GAMEPAD // 游戏手柄
                  | SDL_INIT_EVENTS  // 逝件
                  ))
    {
        throw Error::InitException("SDL", SDL_GetError());
    }
    if (not TTF_Init())
    {
        throw Error::InitException("SDL_ttf", ":(藕也不击倒");
    }
}
void QuitSdlModule()
{
    TTF_Quit();
    SDL_Quit();
}
} // namespace OpenGame::sdl3_h
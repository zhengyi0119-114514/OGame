#include "og.hpp"
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
namespace open_stg::sdl3_h
{
void InitSdlModule()
{
    SPDLOG_INFO("SDL Module init start.");
    if (!SDL_Init(SDL_INIT_VIDEO   // 图形
                 | SDL_INIT_AUDIO // 音频
                 // | SDL_INIT_JOYSTICK // 操纵杆
                 | SDL_INIT_HAPTIC  // 触屏
                 | SDL_INIT_GAMEPAD // 游戏手柄
                 | SDL_INIT_EVENTS  // 逝件
                 ))
    {
        throw error_h::InitException("SDL", SDL_GetError());
    }
    if (!TTF_Init())
    {
        throw error_h::InitException("SDL_ttf",":(藕也不击倒");
    }

}
void QuitSdlModule()
{
    TTF_Quit();
    SDL_Quit();
}
} // namespace open_stg::sdl3_h
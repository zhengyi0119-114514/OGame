#include "spdlog/spdlog.h"
#include "views/renderer.hpp"
#include "views/windows.hpp"
#include <SDL2/SDL.h>
#include <yaml-cpp/yaml.h>

#undef main
[[noreturn]]
void Quit(bool bIsFail)
{
    SDL_VideoQuit();
    SDL_VideoQuit();
    SDL_Quit();
    if (bIsFail)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}
int main(int argc, char **args)
{
    // init
    spdlog::info("Hello world!");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        spdlog::error("SDL2 init fail.");
        Quit(true);
    }
    // sdl2
    ogame::views::sdlWindow window =
        SDL_CreateWindow("SB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (window == nullptr)
    {
        spdlog::error("SDL2 create window fail.");
        spdlog::error(SDL_GetError());
        Quit(true);
    }
    ogame::views::sdlRenderer renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        spdlog::error("SDL2 create renderer fail.");
        spdlog::error(SDL_GetError());
        Quit(true);
    }
    bool bIsRun = true;
    while (bIsRun)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                spdlog::info("exit");
                Quit(false);
                bIsRun = false;
                break;
            default:
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

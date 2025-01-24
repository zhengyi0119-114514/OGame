#include "modules/Config.hpp"
#include "spdlog/spdlog.h"
#include "views/renderer.hpp"
#include "views/windows.hpp"
#include <SDL2/SDL.h>
#include <iostream>

#undef main
[[noreturn]]
void Quit(bool bIsFail)
{
    SDL_AudioQuit();
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
    ogame::config::CONFIG config{720, 1280};
    // init
    spdlog::info("Hello world!");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        spdlog::error("SDL2 init fail.");
        spdlog::error(SDL_GetError());

        Quit(true);
    }
    std::filesystem::path pConfigFilePath = ogame::config::GetConfigFilePath();
    spdlog::info("Config file at" + pConfigFilePath.string());
    // sdl2
    ogame::views::sdlWindow window = SDL_CreateWindow("SB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                      config.iWindowHeight, config.iWindowWidth, 0);

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
                bIsRun = false;
                ogame::config::SetConfigToFile(ogame::config::GetConfigFilePath(), config);
                Quit(false);
                break;
            default:
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

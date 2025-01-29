#include "Modules/Config.hpp"
#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Window.hh>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>

void Init()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
    {
        SPDLOG_ERROR(std::format("SDL2 init fail ,{:}", SDL_GetError()));
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() < 0)
    {
        SPDLOG_ERROR(std::format("SDL2_ttf init fail ,{:}", TTF_GetError()));
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP) < 0)
    {
        SPDLOG_ERROR(std::format("SDL2_image init fail ,{:}", IMG_GetError()));
        exit(EXIT_FAILURE);
    }
    SPDLOG_INFO("Init success");
}
[[noreturn]]
void Quit()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}
int main(int argc, char **argv)
{
    SPDLOG_INFO("Hello world");
    auto path = OGame::Config::GetConfigFileDirectory();
    SPDLOG_INFO(std::format("Config file at {:}.", path.string()));
    Init();
    OGame::Config::CreateDirectoryIfNotExists(path);

    OGame::Config::WINDOW_CONFIG cfg;
    OGame::Config::GetWindowConfig(cfg);

    SDL2pp::Window window{SDL_CreateWindow(cfg.WindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           (int)cfg.WindowWidth, (int)cfg.WindowHeight,
                                           SDL_WINDOW_SHOWN | cfg.WindowFlag)};
    if (window.Get() == NULL)
    {
        SPDLOG_ERROR(std::format("Fail to create window {:}", SDL_GetError()));
    }
    SDL2pp::Renderer renderer{SDL_CreateRenderer(window.Get(),-1,0)};
    if (renderer.Get()==NULL)
    {
        SPDLOG_ERROR(std::format("Fail to create renderer {:}", SDL_GetError()));
    }
    SDL_Event event{};
    bool bIsRun{true};
    while (bIsRun)
    {
        renderer.SetDrawColor(SDL2pp::Color(0,0,102));
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                bIsRun = false;
                break;
            }
        }
        renderer.Present();
        renderer.Clear();
    }
    Quit();
}
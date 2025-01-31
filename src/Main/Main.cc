#include "Modules/Config.hpp"
#include "Resource.hh"
#include "Views/Pages.hpp"
#include <SDL2/SDL.h>
#include <SDL2pp/Color.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Surface.hh>
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

using OGame::Config::GetConfigFileDirectory;

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
    auto path = GetConfigFileDirectory();
    SPDLOG_INFO(std::format("Config file at {:}.", path.string()));
    Init();
    OGame::Config::CreateDirectoryIfNotExists(path);

    OGame::Config::WINDOW_CONFIG cfg{};
    OGame::Config::GetWindowConfig(cfg);

    SDL_Window* pWindow{SDL_CreateWindow(cfg.WindowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           (int)cfg.WindowWidth, (int)cfg.WindowHeight,
                                           SDL_WINDOW_SHOWN)};
    OGame::Resources::IMAGE_RESOURCE imgResource;
    OGame::Resources::GetImageResource(imgResource);
    if (pWindow == NULL)
    {
        SPDLOG_ERROR(std::format("Fail to create window :{:}", SDL_GetError()));
    }
    SDL2pp::Window window{pWindow};
    SDL2pp::Surface windowSurface{SDL_GetWindowSurface(window.Get())};
    OGame::Views::Pages::BasicPage page{window.Get()};
    page.SetBackgroungColor(0,0,102);
    page.EnterMainLoop();
    Quit();
}
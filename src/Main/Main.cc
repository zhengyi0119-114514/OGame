#include "Modules/Config.hpp"
#include "Modules/Math.hh"
#include "Modules/Text.hxx"
#include "Resource.hh"
#include "Views/Controls.hxx"
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
#include <format>
#include <memory>
#include <spdlog/spdlog.h>
#include <utility>

void Init()
{
    OGame::Resources::Text::GetText();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
    OGame::Config::InitWindowConfig();
    OGame::Resources::Text::InitText();

    SPDLOG_INFO("Init success");
}
[[noreturn]]
void Quit()
{
    OGame::Resources::FreeResource();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}
int main(int argc, char **argv)
{
    SPDLOG_INFO("Hello world.");
    Init();

    SPDLOG_DEBUG(std::format("Current directory at {:}", std::filesystem::current_path().string()));
    SPDLOG_DEBUG(std::format("Config file at {:}.", path.string()));

    OGame::Config::WINDOW_CONFIG cfg = OGame::Config::WindowConfig();
    SPDLOG_INFO(std::format("Window width:{:},height:{:}", cfg.WindowWidth, cfg.WindowHeight));

    SDL_Window *pWindow{SDL_CreateWindow(OGame::Resources::Text::GetText().Title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED, (int)cfg.WindowWidth, (int)cfg.WindowHeight,
                                         SDL_WINDOW_SHOWN)};
    OGame::Resources::GetResources();
    if (pWindow == NULL)
    {
        SPDLOG_ERROR(std::format("Fail to create window :{:}", SDL_GetError()));
    }
    SDL2pp::Window window{pWindow};
    OGame::Views::Pages::BasicPage page{window.Get()};
    std::shared_ptr<OGame::Views::Controls::ControlRIIA> formatText(
        new OGame::Views::Controls::ControlRIIA{new OGame::Views::Controls::FormatText(
            OGame::Modules::Math::Point{10, 10}, "杂鱼～～～\n杂鱼～～～~~~\n傻逼")});

    page.AddControl(std::move(formatText));
    page.SetBackgroungColor(0, 0, 102);

    page.EnterMainLoop();
    Quit();
}

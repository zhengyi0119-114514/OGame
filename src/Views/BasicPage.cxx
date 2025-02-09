#include "Modules/Math.hh"
#include "Views/Controls.hxx"
#include "Views/Pages.hpp"
#include <SDL2pp/Color.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Surface.hh>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_surface.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <cmath>
#include <cstdint>
#include <spdlog/spdlog.h>

namespace OGame::Views::Pages
{
static Uint64 s_PreFrameTime;
void BasicPage::EnterMainLoop()
{
    bool isExit = false;
    OGame::Views::Controls::Text text{OGame::Modules::Math::Point{10, 10}, "～文本～"};
    while (!isExit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isExit = true;
                break;
            }
        }
        for(const auto& control :m_ControlList)
        {
            (*control).Get()->Display(m_BaseSurface.Get());
        }
        SDL_UpdateWindowSurface(m_Window);
        BasicPage::Wait(30.0);
    }
}

BasicPage::~BasicPage() noexcept
{
}
BasicPage::BasicPage(SDL_Window *const &window) : m_Window(window)
{
}
void BasicPage::Wait(double maxFps)
{
    // 当前时间 (ms)
    Uint64 currentTime = SDL_GetTicks64();
    // 时间差 (ms)
    Uint64 timeDifference = currentTime - s_PreFrameTime;
    // 应等待时间
    Uint64 timeShouldWait = static_cast<Uint64>(floor(1'000.0 / maxFps));
    // 等待时间
    int64_t timeToWait = timeShouldWait - timeDifference;
    if (timeToWait > 0)
    {
        SDL_Delay(timeToWait);
    }
    s_PreFrameTime = currentTime;
}
void BasicPage::SetBackgroungColor(Uint8 r, Uint8 g, Uint8 b)
{
    this->m_BackGroundColor = SDL2pp::Color{r, g, b};
}
void BasicPage::AddControl(std::shared_ptr<OGame::Views::Controls::ControlRIIA> control)
{
    m_ControlList.push_back(control);
}
} // namespace OGame::Views::Pages
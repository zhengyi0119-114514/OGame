#include "Modules/Math.hh"
#include "Resource.hh"
#include "Views/Controls.hxx"
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
namespace OGame::Views::Controls
{
void FormatText::Display(SDL_Renderer *const &renderer)
{
    std::istringstream stringSteam{m_Text};
    std::string line{};
    OGame::Modules::Math::Point position = m_Position;
    OGame::Modules::Math::Rectangle size{0, 0};
    auto font = OGame::Resources::GetResources().CEFFontsCJKMonoFont;
    TTF_SetFontSize(font, m_FontSize);
    SDL_Rect rect{};
    while (std::getline(stringSteam, line))
    {
        SDL2pp::Surface textSurface(TTF_RenderUTF8_Solid(font, line.c_str(), this->TextColor()));
        SDL2pp::Texture textTexure(SDL_CreateTextureFromSurface(renderer, textSurface.Get()));
        rect.x = m_Position.GetX();
        rect.y = m_Position.GetY() + size.GetHight();
        rect.w = textSurface.GetWidth();
        rect.h = textSurface.GetHeight();

        SDL_RenderCopy(renderer, textTexure.Get(), NULL, &rect);
        // SDL_BlitSurface(textSurface.Get(), NULL, surface, &rect);
        size.SetHight(textSurface.GetHeight() + size.GetHight());
        size.SetWidth(std::max((int)size.GetWidth(), textSurface.GetWidth()));
    }
    this->m_Size = size;
}
} // namespace OGame::Views::Controls
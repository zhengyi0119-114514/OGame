#include "Resource.hh"
#include "Views/Controls.hxx"
#include <SDL2pp/Color.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL_pixels.h>
#include <SDL_power.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <format>
#include <spdlog/spdlog.h>
#include <string>
namespace OGame::Views::Controls
{
Text::Text(Modules::Math::Point position, std::string_view text, OGame::Modules::Math::Rectangle size)
    : m_Position(position), m_Text(text), m_Size(size)
{
}
void Text::SetText(std::string_view value)
{
    this->m_Text = std::string(value);
}
void Text::Display(SDL_Surface *const &surface)
{
    SDL2pp::Surface textSurface(TTF_RenderText_Solid(OGame::Resources::GetResources().CEFFontsCJKMonoFont,
                                                     this->m_Text.c_str(), SDL2pp::Color{255, 255, 255}));
    SDL_Rect rect{};
    SPDLOG_INFO(std::format("Surface width:{:}, hidth:{:}", textSurface.GetWidth(), textSurface.GetWidth()));
    rect.w = textSurface.Get()->w;
    rect.h = textSurface.Get()->h;
    rect.x = m_Position.GetX();
    rect.y = m_Position.GetY();
    SDL_BlitSurface(textSurface.Get(),NULL,surface,&rect);
}
} // namespace OGame::Views::Controls
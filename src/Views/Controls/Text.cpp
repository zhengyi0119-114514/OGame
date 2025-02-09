#include "Modules/Math.hh"
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
#include <cstdint>
#include <format>
#include <spdlog/spdlog.h>
#include <string>
namespace OGame::Views::Controls
{
Text::Text(Modules::Math::Point position, std::string_view text, uint32_t size)
    : m_Position(position), m_Text(text), m_FontSize(size), m_TextColor(255, 255, 255), m_Size(0, 0)
{
}
void Text::SetText(std::string_view value)
{
    this->m_Text = std::string(value);
}
void Text::Display(SDL_Surface *const &surface)
{
    auto font = OGame::Resources::GetResources().CEFFontsCJKMonoFont;
    TTF_SetFontSize(font, (int)m_FontSize);
    SDL2pp::Surface textSurface(TTF_RenderUTF8_Solid(font, this->m_Text.c_str(), this->m_TextColor));

    m_Size = OGame::Modules::Math::Rectangle{(uint32_t)textSurface.Get()->w, (uint32_t)textSurface.Get()->h};

    SDL_Rect rect{};
    rect.x = m_Position.GetX();
    rect.y = m_Position.GetY();
    SDL_BlitSurface(textSurface.Get(), NULL, surface, &rect);
}
} // namespace OGame::Views::Controls
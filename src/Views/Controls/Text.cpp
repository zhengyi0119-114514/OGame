#include "Modules/Math.hh"
#include "Resource.hh"
#include "Views/Controls.hxx"
#include <SDL2pp/Color.hh>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Texture.hh>
#include <SDL_pixels.h>
#include <SDL_power.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <cstdint>
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
void Text::Display(SDL_Renderer *const &renderer)
{
    auto font = OGame::Resources::GetResources().CEFFontsCJKMonoFont;
    TTF_SetFontSize(font, (int)m_FontSize);
    SDL2pp::Surface textSurface(TTF_RenderUTF8_Solid(font, this->m_Text.c_str(), this->m_TextColor));
    m_Size = {(uint32_t)textSurface.GetWidth(), (uint32_t)textSurface.GetHeight()};
    SDL2pp::Texture textTexure(SDL_CreateTextureFromSurface(renderer, textSurface.Get()));
    SDL_Rect rect{m_Position.GetX(), m_Position.GetY(), textSurface.GetWidth(), textSurface.GetHeight()};
    SDL_RenderCopy(renderer, textTexure.Get(), NULL, &rect);
}
} // namespace OGame::Views::Controls
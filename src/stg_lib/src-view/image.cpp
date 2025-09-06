#include "og_view.hpp"
namespace OpenGame::View
{
Image::Image(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer *pRenderer, Math::Point location)
    : m_spTexture(SDL_CreateTextureFromSurface(pRenderer, spSurface)), m_spLocation(location)
{
}
Image::Image(sdl3_h::SharedPtrTexture spTexture, Math::Point spLocation)
    : m_spTexture(spTexture), m_spLocation(spLocation)
{
}
Math::Size Image::getTextureSize()
{
    float width{}, height{};
    SDL_GetTextureSize(m_spTexture, &width, &height);
    return {width, height};
}
void Image::PrintToRenderer(SDL_Renderer *pRenderer, Math::Size s)
{
    SDL_FRect rect{static_cast<float>(m_spLocation.x), static_cast<float>(m_spLocation.y), static_cast<float>(s.width),
                   static_cast<float>(s.height)};
    if (s.IsUndefined())
    {
        float width{}, height{};
        SDL_GetTextureSize(m_spTexture, &width, &height);
        rect.w = width;
        rect.h = height;
    }
    SDL_RenderTexture(pRenderer, m_spTexture, NULL, &rect);
}
void Image::ResetLocation(Math::Point spLocation) noexcept
{
    m_spLocation = spLocation;
}
void Image::SetLocation(Math::Point p) noexcept
{
    m_spLocation = p;
}
} // namespace OpenGame::View

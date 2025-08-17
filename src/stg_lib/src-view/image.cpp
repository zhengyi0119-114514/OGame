#include "og_view.hpp"
namespace open_stg::view_h
{
Image::Image(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer *pRenderer, math_h::Point location, math_h::Size sSize)
    : m_spTexture(SDL_CreateTextureFromSurface(pRenderer, spSurface)), m_spLocation(location),
      m_pImageSize(getTextureSize())
{
}
Image::Image(sdl3_h::SharedPtrTexture spTexture, math_h::Point spLocation, math_h::Size sSize)
    : m_spTexture(spTexture), m_spLocation(spLocation), m_pImageSize(getTextureSize())
{
}
math_h::Size Image::getTextureSize()
{
    float width{}, height{};
    SDL_GetTextureSize(m_spTexture, &width, &height);
    return {width, height};
}
void Image::PrintToRenderer(SDL_Renderer *pRenderer)
{
    SDL_FRect rect{static_cast<float>(m_spLocation.x), static_cast<float>(m_spLocation.y),
                   static_cast<float>(m_pImageSize.width), static_cast<float>(m_pImageSize.height)};
    SDL_RenderTexture(pRenderer, m_spTexture, NULL, &rect);
}
void Image::ResetLocation(math_h::Point spLocation)
{
    m_spLocation = spLocation;
}
void Image::SetLocation(math_h::Point p) noexcept
{
    m_spLocation = p;
}
} // namespace open_stg::view_h

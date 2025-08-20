#include "og.hpp"
namespace open_stg::view_h
{
RotatableImage::RotatableImage(sdl3_h::SharedPtrSurface spSurface, SDL_Renderer *pRenderer, math_h::Point location,
                               double dAngleOfRevolve)
    : Image(spSurface, pRenderer, location)
{
    m_dAngleOfRevole = static_cast<float>(dAngleOfRevolve);
}

RotatableImage::RotatableImage(sdl3_h::SharedPtrTexture spTexture, math_h::Point spLocation, double dAngleOfRevolve)
    : Image(spTexture, spLocation)
{
    m_dAngleOfRevole = static_cast<float>(dAngleOfRevolve);
}
void RotatableImage::SetAngleOfRevolve(double angleOfRotation)
{
    m_dAngleOfRevole = static_cast<float>(angleOfRotation);
}
double RotatableImage::GetAngleOfRevolve() const noexcept
{
    return m_dAngleOfRevole;
}
void RotatableImage::ResetLocation(math_h::Point p) noexcept
{
    m_spLocation = p;
}
void RotatableImage::PrintToRenderer(SDL_Renderer *pRenderer, math_h::Size size)
{
    float fTextureWidth{}, fTextureHeight{};
    int iRendererWidth{}, iRendererHeight{};
    SDL_GetTextureSize(m_spTexture, &fTextureWidth, &fTextureHeight);
    SDL_GetCurrentRenderOutputSize(pRenderer, &iRendererWidth, &iRendererHeight);
    double dAngleOfRevolve = m_dAngleOfRevole * 180 / M_PI;
    SDL_FRect dstRect{
        .x = (iRendererWidth - fTextureWidth) / 2.0f,
        .y = (iRendererHeight - fTextureHeight) / 2.0f,
        .w = fTextureWidth,
        .h = fTextureHeight,
    };
    SDL_RenderTextureRotated(/*renderer*/ pRenderer, /*texture*/ m_spTexture, /*srcrect*/ nullptr,
                             /*dstrect */ &dstRect, /*angle(角度制)*/ dAngleOfRevolve, /*center*/ nullptr, SDL_FLIP_NONE);
}

} // namespace open_stg::view_h
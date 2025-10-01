#include "og_error_h.hpp"
#include "og_sdl3_h.hpp"
#include <SDL3_image/SDL_image.h>
namespace OpenGame::SDL3
{
void Surface::_DestroyObject(SDL_Surface *pSurface)
{
    SDL_DestroySurface(m_p);
}
Surface::Surface(std::filesystem::path pImageFilePath)
    : PtrSdlObjectTemplate<SDL_Surface>(IMG_Load(pImageFilePath.string().c_str()))
{
    if (!RefThis.Get())
        throw Error::SDLException(NameOf(Surface));
}
Surface::Surface(Int iSurfaceWidth, Int iSurfaceHeigt, SDL_PixelFormat pf)
    : Surface(SDL_CreateSurface(iSurfaceWidth, iSurfaceHeigt, pf))
{
    if (!RefThis.Get())
        throw Error::SDLException(NameOf(Surface));
}
void Surface::SetColorspace(Colorspace cs)
{
    if (!SDL_SetSurfaceColorspace(RefThis.Get(), StaticCast<SDL_Colorspace>(cs)))
        throw Error::SDLException(NameOf(Surface));
}
Colorspace Surface::GetColorspace() const
{
    return StaticCast<Colorspace>(SDL_GetSurfaceColorspace(RefThis.Get()));
}
SDL_Palette *Surface::CreatePalette()
{
    return SDL_CreateSurfacePalette(RefThis.Get());
}
} // namespace OpenGame::SDL3

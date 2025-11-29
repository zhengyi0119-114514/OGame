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
Surface::Surface(int iSurfaceWidth, int iSurfaceHeigt, SDL_PixelFormat pf)
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
void Surface::AddAlternateImage(SDL_Surface *pImage)
{
    if (!SDL_AddSurfaceAlternateImage(RefThis.Get(), pImage))
        throw Error::SDLException(NameOf(Surface));
}
bool Surface::HasAlternateImage() const
{
    return SDL_SurfaceHasAlternateImages(RefThis.Get());
}
std::span<SDL_Surface *> Surface::GetSurfaceImages() const
{
    int iCountOfSurfaceImages = 0;
    VAR ss = SDL_GetSurfaceImages(RefThis.Get(), &iCountOfSurfaceImages);
    if (!ss)
        throw Error::SDLException(NameOf(Surface));
    return {ss, StaticCast<size_t>(iCountOfSurfaceImages)};
}
void Surface::RemoveAlternateImages()
{
    SDL_RemoveSurfaceAlternateImages(RefThis.Get());
}
void Surface::Lock()
{
    SDL_LockSurface(RefThis.Get());
}
void Surface::Unlock()
{
    SDL_UnlockSurface(RefThis.Get());
}
void Surface::SetRLE(bool bEnable)
{
    if (!SDL_SetSurfaceRLE(RefThis.Get(), bEnable))
        throw Error::SDLException(NameOf(Surface));
}
bool Surface::GetRLE() const
{
    return SDL_SurfaceHasRLE(RefThis.Get());
}
} // namespace OpenGame::SDL3

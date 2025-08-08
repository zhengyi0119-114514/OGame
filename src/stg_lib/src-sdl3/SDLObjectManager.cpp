#include "og.hpp"
namespace open_stg::sdl3_h
{
void SurfaceManager::DestoryObject(SDL_Surface *p)
{
    if (p != nullptr)
    {
        SDL_DestroySurface(p);
    }
}
void TextureManager::DestoryObject(SDL_Texture* p)
{
    if(p!=nullptr)
    {
        SDL_DestroyTexture(p);
    }
}
void RendererManager::DestoryObject(SDL_Renderer* p)
{
    if(p!=nullptr)
    {
        SDL_DestroyRenderer(p);
    }
}
} // namespace open_stg::sdl3_h
#include "og_sdl3_h.hpp"
namespace OpenGame::SDL3
{
    void Renderer::_DestroyObject(SDL_Renderer * pRenderer)
    {
        SDL_DestroyRenderer(pRenderer);
    }
}

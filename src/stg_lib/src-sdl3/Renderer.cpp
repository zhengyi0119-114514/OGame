#include "og_sdl3_h.hpp"
namespace OpenGame::SDL3
{
void Renderer::_DestroyObject(SDL_Renderer *pRenderer)
{
    SDL_DestroyRenderer(pRenderer);
}
// Renderer::Renderer(Renderer &&rrv) :PtrSdlObjectTemplate<SDL_Renderer>(std::move(rrv))
// {
// }
// Renderer& Renderer::operator=(Renderer&& rsh)
// {
//     PtrSdlObjectTemplate<SDL_Renderer>::operator=(std::move(rsh));
//     return RefThis;
// }
} // namespace OpenGame::SDL3

#include "views/renderer.hpp"

namespace ogame::views
{
sdlRenderer::~sdlRenderer()
{
    SDL_DestroyRenderer(this->m_pRenderer);
}
sdlRenderer::operator SDL_Renderer *() const
{
    return this->m_pRenderer;
}
sdlRenderer::sdlRenderer(SDL_Renderer *p) : m_pRenderer{p}
{
}
} // namespace ogame::views
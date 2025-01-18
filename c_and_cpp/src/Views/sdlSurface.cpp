#include "views/Surface.hpp"
namespace ogame::views
{
sdlSurface::sdlSurface(SDL_Surface *s) : m_pSurface{s}
{
}
sdlSurface::~sdlSurface()
{
    SDL_FreeSurface(m_pSurface);
}
sdlSurface::operator SDL_Surface *() const
{
    return this->m_pSurface;
}
} // namespace ogame::views
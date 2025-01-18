#include <SDL2/SDL.h>
#ifndef OGAME_HEAD_VIEWS_SURFACE
#define OGAME_HEAD_VIEWS_SURFACE
namespace ogame::views
{
class sdlSurface
{
  private:
    SDL_Surface *m_pSurface;

  public:
    sdlSurface(SDL_Surface *pSurface);
    sdlSurface(const sdlSurface &) = delete;
    sdlSurface& operator=(const sdlSurface&) = delete;
    operator SDL_Surface *() const;
    virtual ~sdlSurface();
};
} // namespace ogame::views
#endif
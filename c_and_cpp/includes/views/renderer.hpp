#include <SDL.h>
#ifndef OGAME_HEAD_VIEWS_RENDERER
#define OGAME_HEAD_VIEWS_RENDERER
namespace ogame::views
{
class sdlRenderer
{
  private:
    SDL_Renderer *m_pRenderer;

  public:
    sdlRenderer(SDL_Renderer *pRenderer);
    sdlRenderer(const sdlRenderer &) = delete;
    virtual ~sdlRenderer();
    operator SDL_Renderer *() const;
    sdlRenderer &operator=(const sdlRenderer &) = delete;
};
} // namespace ogame::views
#endif
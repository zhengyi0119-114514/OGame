#include <SDL.h>
#ifndef OGAME_HEAD_VIEWS_WINDOWS
#define OGAME_HEAD_VIEWS_WINDOWS
namespace ogame::views
{
class sdlWindow
{
  private:
    SDL_Window *m_pWindow;

  public:
    virtual ~sdlWindow();
    sdlWindow(SDL_Window *pWindow);
    sdlWindow(const sdlWindow &) = delete;
    operator SDL_Window *() const;
    sdlWindow &operator=(const sdlWindow &) = delete;
};
} // namespace ogame::views
#endif
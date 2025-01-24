#include <SDL.h>
#include <memory>
#include <vector>
#include "Controls.hpp"
#ifndef OGAME_HEAD_VIEWS_WINDOWS
#define OGAME_HEAD_VIEWS_WINDOWS
namespace ogame::views
{
class sdlWindow
{

  public:
    virtual ~sdlWindow();
    sdlWindow(SDL_Window *pWindow);
    sdlWindow(const sdlWindow &) = delete;
    operator SDL_Window *() const;
    sdlWindow &operator=(const sdlWindow &) = delete;
    void AddSubControl(std::shared_ptr<IControl> c);
    

  private:
    SDL_Window *m_pWindow;
    std::vector<std::shared_ptr<IControl>> m_controlsList;
};
} // namespace ogame::views
#endif

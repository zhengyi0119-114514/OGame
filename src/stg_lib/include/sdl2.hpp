#ifndef OGAME_STGLIB_SDL2_H
#define OGAME_STGLIB_SDL2_H
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>
namespace open_stg::sdl2_h
{
class PtrWindow
{
  private:
    SDL_Window *m_pWin = nullptr;

  public:
    PtrWindow(SDL_Window *pWin);
    PtrWindow(const PtrWindow &) = delete;
    PtrWindow(PtrWindow &&ref);
    PtrWindow &operator=(const PtrWindow &rsh) = delete;
    PtrWindow &operator=(PtrWindow &&rsh);
    void Swap(PtrWindow &ref);
    void swap(PtrWindow &ref)
    {
        this->Swap(ref);
    }
    ~PtrWindow() noexcept;
    const SDL_Window *operator->() const;
    SDL_Window *operator->();
    const SDL_Window &operator*() const;
    SDL_Window &operator*();
    SDL_Window *const *operator&() const;
    SDL_Window **operator&();
    operator SDL_Window *() const noexcept;
};
using ptr_window = PtrWindow;
class PtrRenderer
{
  private:
    SDL_Renderer *m_pRend = nullptr;

  public:
    PtrRenderer(SDL_Renderer *pRend);
    PtrRenderer(const PtrRenderer &) = delete;
    PtrRenderer(PtrRenderer &&r);
    PtrRenderer &operator=(const PtrRenderer &rsh) = delete;
    PtrRenderer &operator=(PtrRenderer &&rsh);
    void Swap(PtrRenderer &ref);
    void swap(PtrRenderer &ref)
    {
        this->Swap(ref);
    }
    ~PtrRenderer() noexcept;
};
using ptr_renderer = PtrRenderer;
} // namespace open_stg::sdl2_h
#endif

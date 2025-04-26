#ifndef OGAME_STGLIB_SDL2_H
#define OGAME_STGLIB_SDL2_H
#include <SDL2/SDL.h>

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
    SDL_Window *Get() const;
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
    SDL_Renderer **operator&();
    SDL_Renderer *const *operator&() const;
    SDL_Renderer &operator*();
    const SDL_Renderer &operator*() const;
    SDL_Renderer *operator->();
    const SDL_Renderer *operator->() const;
    operator SDL_Renderer *() const noexcept;
    SDL_Renderer *Get() const;
};
using ptr_renderer = PtrRenderer;
class PtrSurface
{
  public:
    PtrSurface(SDL_Surface *pSurf);
    PtrSurface(PtrSurface &&);
    PtrSurface(const PtrSurface &) = delete;
    PtrSurface &operator=(PtrSurface &&);
    PtrSurface &operator=(const PtrSurface &) = delete;
    ~PtrSurface() noexcept;
    void Swap(PtrSurface &ref);
    void swap(PtrSurface &ref)
    {
        this->Swap(ref);
    }
    SDL_Surface **operator&();
    SDL_Surface *const *operator&() const;
    SDL_Surface &operator*();
    const SDL_Surface &operator*() const;
    SDL_Surface *operator->();
    const SDL_Surface *operator->() const;
    SDL_Surface *Get() const;

  private:
    SDL_Surface *m_pSurf = nullptr;
};
using ptr_surface = PtrSurface;
} // namespace open_stg::sdl2_h
#endif

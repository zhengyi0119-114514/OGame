#ifndef OGAME_STGLIB_SDL2_H
#define OGAME_STGLIB_SDL2_H
#include <SDL2/SDL.h>
#undef main
#include <memory>

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
    PtrSurface &operator=(PtrSurface &&) noexcept;
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

class SharedPtrWindow
{
  private:
    std::shared_ptr<PtrWindow> m_window;

  public:
    SharedPtrWindow(SDL_Window *pWin);
    SharedPtrWindow(const SharedPtrWindow &) = default;
    SharedPtrWindow(SharedPtrWindow &&) = default;
    SharedPtrWindow &operator=(const SharedPtrWindow &) = default;
    SharedPtrWindow &operator=(SharedPtrWindow &&) = default;

    const SDL_Window *operator->() const;
    SDL_Window *operator->();
    const SDL_Window &operator*() const;
    SDL_Window &operator*();
    operator SDL_Window *() const noexcept;
    SDL_Window *Get() const;
};
using shared_ptr_window = SharedPtrWindow;

class SharedPtrRenderer
{
  private:
    std::shared_ptr<PtrRenderer> m_renderer;

  public:
    SharedPtrRenderer(SDL_Renderer *pRend);
    SharedPtrRenderer(const SharedPtrRenderer &) = default;
    SharedPtrRenderer(SharedPtrRenderer &&) = default;
    SharedPtrRenderer &operator=(const SharedPtrRenderer &) = default;
    SharedPtrRenderer &operator=(SharedPtrRenderer &&) = default;

    const SDL_Renderer *operator->() const;
    SDL_Renderer *operator->();
    const SDL_Renderer &operator*() const;
    SDL_Renderer &operator*();
    operator SDL_Renderer *() const noexcept;
    SDL_Renderer *Get() const;
};
using shared_ptr_renderer = SharedPtrRenderer;

class SharedPtrSurface
{
  private:
    std::shared_ptr<PtrSurface> m_surface;

  public:
    SharedPtrSurface(SDL_Surface *pSurf);
    SharedPtrSurface(const SharedPtrSurface &) = default;
    SharedPtrSurface(SharedPtrSurface &&) = default;
    SharedPtrSurface &operator=(const SharedPtrSurface &) = default;
    SharedPtrSurface &operator=(SharedPtrSurface &&) = default;

    const SDL_Surface *operator->() const;
    SDL_Surface *operator->();
    const SDL_Surface &operator*() const;
    SDL_Surface &operator*();
    operator SDL_Surface *() const noexcept;
    SDL_Surface *Get() const;
};
using shared_ptr_surface = SharedPtrSurface;
class PtrTexture {
private:
    SDL_Texture* m_pTex = nullptr;
public:
    PtrTexture(SDL_Texture* pTex);
    PtrTexture(const PtrTexture&) = delete;
    PtrTexture(PtrTexture&& other);
    PtrTexture& operator=(const PtrTexture&) = delete;
    PtrTexture& operator=(PtrTexture&&);
    void Swap(PtrTexture& ref);
    void swap(PtrTexture& ref) { this->Swap(ref); }
    ~PtrTexture() noexcept;
    const SDL_Texture& operator*() const;
    SDL_Texture& operator*();
    SDL_Texture* const* operator&() const;
    SDL_Texture** operator&();
    operator SDL_Texture*() const noexcept;
    SDL_Texture* Get() const;
};
using ptr_texture = PtrTexture;
class SharedPtrTexture {
private:
    std::shared_ptr<PtrTexture> m_texture;
public:
    SharedPtrTexture(SDL_Texture* pTex);
    SharedPtrTexture(const SharedPtrTexture&) = default;
    SharedPtrTexture(SharedPtrTexture&&) = default;
    SharedPtrTexture& operator=(const SharedPtrTexture&) = default;
    SharedPtrTexture& operator=(SharedPtrTexture&&) = default;

    const SDL_Texture* operator->() const;
    SDL_Texture* operator->();
    const SDL_Texture& operator*() const;
    SDL_Texture& operator*();
    operator SDL_Texture*() const noexcept;
    SDL_Texture* Get() const;
};
using shared_ptr_texture = SharedPtrTexture;
} // namespace open_stg::sdl2_h
#endif

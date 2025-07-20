/**
 * @file sdl.hpp
 * @author ICE_THORN :(
 * @brief 
 * @date 2025-07-19
 */
#ifndef OGAME_STGLIB_SDL2_H
#define OGAME_STGLIB_SDL2_H
#include <SDL2/SDL.h>
#ifdef main
#undef main
#endif

#include <memory>

namespace open_stg::sdl2_h
{
/**
 * @brief [SDL对象的RIIA包装类的基类]
 *
 */
class ptr_sdl_obj
{
  public:
    virtual ~ptr_sdl_obj() noexcept = default;
};
using PtrSDLObject = ptr_sdl_obj;
class PtrWindow : public PtrSDLObject
{
  private:
    SDL_Window *m_pWin = nullptr;

  public:
    PtrWindow(SDL_Window *pWin);
    PtrWindow(const PtrWindow &) = delete;
    PtrWindow(PtrWindow &&ref) noexcept;
    PtrWindow &operator=(const PtrWindow &rsh) = delete;
    PtrWindow &operator=(PtrWindow &&rsh) noexcept;
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
    operator SDL_Window *() const noexcept;
    SDL_Window *Get() const;
    SDL_Window *data() const;
    SDL_Window *get() const;
};
using ptr_window = PtrWindow;

class PtrRenderer : public PtrSDLObject
{
  private:
    SDL_Renderer *m_pRend = nullptr;

  public:
    PtrRenderer(SDL_Renderer *pRend);
    PtrRenderer(const PtrRenderer &) = delete;
    PtrRenderer(PtrRenderer &&r) noexcept;
    PtrRenderer &operator=(const PtrRenderer &rsh) = delete;
    PtrRenderer &operator=(PtrRenderer &&rsh) noexcept;
    void Swap(PtrRenderer &ref);
    void swap(PtrRenderer &ref)
    {
        this->Swap(ref);
    }
    ~PtrRenderer() noexcept;
    SDL_Renderer &operator*();
    const SDL_Renderer &operator*() const;
    SDL_Renderer *operator->();
    const SDL_Renderer *operator->() const;
    operator SDL_Renderer *() const noexcept;
    SDL_Renderer *Get() const;
    SDL_Renderer *data() const;
    SDL_Renderer *get() const;
};
using ptr_renderer = PtrRenderer;
class PtrSurface : public PtrSDLObject
{
  public:
    PtrSurface(SDL_Surface *pSurf);
    PtrSurface(PtrSurface &&) noexcept;
    PtrSurface(const PtrSurface &) = delete;
    PtrSurface &operator=(PtrSurface &&) noexcept;
    PtrSurface &operator=(const PtrSurface &) = delete;
    ~PtrSurface() noexcept;
    void Swap(PtrSurface &ref);
    void swap(PtrSurface &ref)
    {
        this->Swap(ref);
    }
    SDL_Surface &operator*();
    const SDL_Surface &operator*() const;
    SDL_Surface *operator->();
    const SDL_Surface *operator->() const;
    SDL_Surface *Get() const;
    SDL_Surface *data() const;
    SDL_Surface *get() const;

  private:
    SDL_Surface *m_pSurf = nullptr;
};
using ptr_surface = PtrSurface;
class PtrTexture
{
  private:
    SDL_Texture *m_pTex = nullptr;

  public:
    PtrTexture(SDL_Texture *pTex);
    PtrTexture(const PtrTexture &) = delete;
    PtrTexture(PtrTexture &&other) noexcept;
    PtrTexture &operator=(const PtrTexture &) = delete;
    PtrTexture &operator=(PtrTexture &&) noexcept;
    void Swap(PtrTexture &ref);
    void swap(PtrTexture &ref)
    {
        this->Swap(ref);
    }
    ~PtrTexture() noexcept;
    const SDL_Texture &operator*() const;
    SDL_Texture &operator*();
    operator SDL_Texture *() const noexcept;
    SDL_Texture *Get() const;
    SDL_Texture *data() const;
    SDL_Texture *get() const;
};

using ptr_texture = PtrTexture;
class SharedPtrWindow : public PtrSDLObject
{
  private:
    std::shared_ptr<PtrWindow> m_spWin;

  public:
    SharedPtrWindow(SDL_Window *pWin);
    virtual ~SharedPtrWindow() noexcept = default;
    void swap(SharedPtrWindow &o) noexcept;
    void Swap(SharedPtrWindow &o) noexcept;
    SDL_Window &operator*();
    SDL_Window &operator*() const;
    SDL_Window *Get() const noexcept;
    SDL_Window *data() const noexcept;
    SDL_Window *get() const noexcept;
    operator SDL_Window *() const noexcept;
};
using shared_ptr_window = SharedPtrWindow;

class SharedPtrRenderer
{
  private:
    std::shared_ptr<PtrRenderer> m_spRend;

  public:
    SharedPtrRenderer(SDL_Renderer *pRend);
    virtual ~SharedPtrRenderer() noexcept = default;
    void Swap(SharedPtrRenderer &o) noexcept;
    void swap(SharedPtrRenderer &o) noexcept;
    SDL_Renderer &operator*();
    SDL_Renderer &operator*() const;
    SDL_Renderer *operator->();
    const SDL_Renderer *operator->() const;
    SDL_Renderer *Get() const noexcept;
    SDL_Renderer *get() const noexcept;
    SDL_Renderer *data() const noexcept;
    operator SDL_Renderer *() const noexcept;
};
using shared_ptr_renderer = SharedPtrRenderer;

class SharedPtrSurface
{
  private:
    std::shared_ptr<PtrSurface> m_spSurf;

  public:
    SharedPtrSurface(SDL_Surface *pSurf);
    virtual ~SharedPtrSurface() noexcept = default;
    void Swap(SharedPtrSurface &o) noexcept;
    void swap(SharedPtrSurface &o) noexcept;
    SDL_Surface &operator*();
    SDL_Surface &operator*() const;
    SDL_Surface *operator->();
    const SDL_Surface *operator->() const;
    SDL_Surface *Get() const noexcept;
    SDL_Surface *get() const noexcept;
    SDL_Surface *data() const noexcept;
    operator SDL_Surface *() const noexcept;
};
using shared_ptr_surface = SharedPtrSurface;

class SharedPtrTexture
{
  private:
    std::shared_ptr<PtrTexture> m_spTex;

  public:
    SharedPtrTexture(SDL_Texture *pTex);
    virtual ~SharedPtrTexture() noexcept = default;
    void Swap(SharedPtrTexture &o) noexcept;
    void swap(SharedPtrTexture &o) noexcept;
    SDL_Texture &operator*();
    SDL_Texture &operator*() const;
    SDL_Texture *operator->();
    const SDL_Texture *operator->() const;
    SDL_Texture *Get() const noexcept;
    SDL_Texture *get() const noexcept;
    SDL_Texture *data() const noexcept;
    operator SDL_Texture *() const noexcept;
};
using shared_ptr_texture = SharedPtrTexture;
} // namespace open_stg::sdl2_h
#endif

/**
 * @file sdl3.hpp
 * @author Ciallo～(∠・ω< )⌒★
 * @brief
 * @version iCEtHORN
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef OGAME_STGLIB_SDL3_H
#define OGAME_STGLIB_SDL3_H 1
#include <SDL3/SDL.h>
#include <concepts>
#include <memory>
#include <utility>
namespace open_stg::sdl3_h
{
void InitSdlModule();
void QuitSdlModule();
class PtrSdlObject
{
  public:
    virtual ~PtrSdlObject() noexcept = default;
};
template <typename TSdlObject, typename TSdlObjectManager>
concept SdlObjectManager = requires(TSdlObject *pobj) { TSdlObjectManager::DestoryObject(pobj); };
template <typename TSdlObject, typename TSdlObjectManager>
    requires SdlObjectManager<TSdlObject, TSdlObjectManager>
class PtrSdlObject_t : public PtrSdlObject
{
  protected:
    TSdlObject *m_p = nullptr;

  public:
    void swap(PtrSdlObject_t &r)
    {
        std::swap(this->m_p, r.m_p);
    }
    PtrSdlObject_t(TSdlObject *p) : m_p(p)
    {
    }
    PtrSdlObject_t(const PtrSdlObject_t &o) = delete;
    PtrSdlObject_t(PtrSdlObject_t &&r)
    {
        m_p = r.m_p;
        r.m_p = nullptr;
    }
    PtrSdlObject_t &operator=(const PtrSdlObject_t &rsh) = delete;
    PtrSdlObject_t &operator=(PtrSdlObject_t &&rsh)
    {
        PtrSdlObject_t obj{std::move(rsh)};
        swap(obj);
        return *this;
    }
    TSdlObject &operator*() const noexcept
    {
        return *this->m_p;
    }
    TSdlObject *operator->() const noexcept
    {
        return m_p;
    }
    operator TSdlObject *() const noexcept
    {
        return m_p;
    }
    virtual ~PtrSdlObject_t() noexcept
    {
        TSdlObjectManager::DestoryObject(m_p);
    }
};
template <typename TSdlObject, typename TSdlObjectManager>
    requires SdlObjectManager<TSdlObject, TSdlObjectManager>
class SharedPtrSdlObject_t : public PtrSdlObject
{
  protected:
    std::shared_ptr<PtrSdlObject_t<TSdlObject, TSdlObjectManager>> m_ptr{nullptr};

  public:
    SharedPtrSdlObject_t(TSdlObject *p) : m_ptr(std::make_shared<PtrSdlObject_t<TSdlObject, TSdlObjectManager>>(p))
    {
    }
    SharedPtrSdlObject_t(const SharedPtrSdlObject_t &) = default;
    SharedPtrSdlObject_t(SharedPtrSdlObject_t &&) = default;
    SharedPtrSdlObject_t &operator=(const SharedPtrSdlObject_t &rsh) = default;
    SharedPtrSdlObject_t &operator=(SharedPtrSdlObject_t &&rsh) = default;
    TSdlObject &operator*() const
    {
        return *(*m_ptr);
    }
    TSdlObject *operator->() const
    {
        return *m_ptr;
    }
    operator TSdlObject *() const
    {
        return *m_ptr;
    }
};
struct SurfaceManager
{
    static void DestoryObject(SDL_Surface *p);
};
template class PtrSdlObject_t<SDL_Surface, SurfaceManager>;
template class SharedPtrSdlObject_t<SDL_Surface, SurfaceManager>;
using PtrSurface = PtrSdlObject_t<SDL_Surface, SurfaceManager>;
using SharedPtrSurface = SharedPtrSdlObject_t<SDL_Surface, SurfaceManager>;
static_assert(std::copyable<SharedPtrSurface> && std::movable<SharedPtrSurface>);
struct TextureManager
{
    static void DestoryObject(SDL_Texture *p);
};
template class PtrSdlObject_t<SDL_Texture, TextureManager>;
template class SharedPtrSdlObject_t<SDL_Texture, TextureManager>;
using PtrTexture = PtrSdlObject_t<SDL_Texture, TextureManager>;
using SharedPtrTexture = SharedPtrSdlObject_t<SDL_Texture, TextureManager>;
struct RendererManager
{
    static void DestoryObject(SDL_Renderer* p);
};
template class PtrSdlObject_t<SDL_Renderer,RendererManager>;
template class SharedPtrSdlObject_t<SDL_Renderer,RendererManager>;
using PtrRenderer = PtrSdlObject_t<SDL_Renderer,RendererManager>;
using SharedPtrRenderer = SharedPtrSdlObject_t<SDL_Renderer,RendererManager>;
} // namespace open_stg::sdl3_h
#endif

/**
 * @file sdl3.hpp
 * @author Ciallo～(∠・ω< )⌒★
 * @brief SDL3 wrapper and utilities[SDL3封装和工具类]
 * @version iCEtHORN
 * @date 2025-08-07
 *
 * Contains:
 * - SDL object management[SDL对象管理]
 * - Smart pointers for SDL resources[SDL资源的智能指针]
 * - Renderer and window utilities[渲染器和窗口工具]
 */
#include "og_math_h.hpp"
#ifndef OGAME_STGLIB_SDL3_H
#define OGAME_STGLIB_SDL3_H 1
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <concepts>
#include <memory>
#include <utility>
namespace open_stg::sdl3_h
{
/**
 * @brief Initialize SDL module[初始化SDL模块]
 */
void InitSdlModule();

/**
 * @brief Quit SDL module[退出SDL模块]
 */
void QuitSdlModule();
/**
 * @brief Base class for SDL smart pointers[SDL智能指针基类]
 */
class PtrSdlObject
{
  public:
    virtual ~PtrSdlObject() noexcept = default; ///< Virtual destructor[虚析构函数]
};
/**
 * @brief Concept for SDL object managers[SDL对象管理器的概念]
 * @tparam TSdlObject SDL object type[SDL对象类型]
 * @tparam TSdlObjectManager Manager type[管理器类型]
 */
template <typename TSdlObject, typename TSdlObjectManager>
concept SdlObjectManager = requires(TSdlObject *pobj) {
    TSdlObjectManager::DestoryObject(pobj); ///< Requires destroy method[需要销毁方法]
};
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
    explicit PtrSdlObject_t(TSdlObject *p) : m_p(p)
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
    TSdlObject *Get() const noexcept
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
    explicit SharedPtrSdlObject_t(TSdlObject *p) : m_ptr(std::make_shared<PtrSdlObject_t<TSdlObject, TSdlObjectManager>>(p))
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
    TSdlObject *Get() const
    {
        return m_ptr->Get();
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
    static void DestoryObject(SDL_Renderer *p);
};
template class PtrSdlObject_t<SDL_Renderer, RendererManager>;
template class SharedPtrSdlObject_t<SDL_Renderer, RendererManager>;
using PtrRenderer = PtrSdlObject_t<SDL_Renderer, RendererManager>;
using SharedPtrRenderer = SharedPtrSdlObject_t<SDL_Renderer, RendererManager>;
struct WindowManager
{
    static void DestoryObject(SDL_Window *p);
};
template class PtrSdlObject_t<SDL_Window, WindowManager>;
template class SharedPtrSdlObject_t<SDL_Window, WindowManager>;
using PtrWindow = PtrSdlObject_t<SDL_Window, WindowManager>;
using SharedPtrWindow = SharedPtrSdlObject_t<SDL_Window, WindowManager>;
struct TtfFontManager
{
    static void DestoryObject(TTF_Font *p);
};
template class PtrSdlObject_t<TTF_Font, TtfFontManager>;
template class SharedPtrSdlObject_t<TTF_Font, TtfFontManager>;
using PtrTtfFont = PtrSdlObject_t<TTF_Font, TtfFontManager>;
using SharedPtrTtfFont = SharedPtrSdlObject_t<TTF_Font, TtfFontManager>;
} // namespace open_stg::sdl3_h
#endif

module;
#include "sdl2.hpp"
#include <SDL.h>
#include <SDL_video.h>
#include <utility>
export module open_stg.sdl2;
export namespace open_stg::sdl2
{
class ptr_window
{
  private:
    open_stg::sdl2_h::PtrWindow m_pWin;

  public:
    ptr_window(SDL_Window *const &window) : m_pWin(window)
    {
    }
    ptr_window(const ptr_window &) = delete;
    ptr_window(ptr_window &&ref) : m_pWin(std::move(ref.m_pWin))
    {
    }
    void swap(ptr_window &ref)
    {
        std::swap(this->m_pWin, ref.m_pWin);
    }
    ptr_window &operator=(const ptr_window &rsh) = delete;
    ptr_window &operator=(ptr_window &&rsh)
    {
        this->m_pWin = std::move(rsh.m_pWin);
        return *this;
    }
    ~ptr_window() noexcept = default;
    SDL_Window *operator->()
    {
        return m_pWin;
    }
    const SDL_Window *operator->() const
    {
        return m_pWin;
    }
    const SDL_Window &operator*() const
    {
        return *m_pWin;
    }
    SDL_Window &operator*()
    {
        return *m_pWin;
    }
    SDL_Window **operator&()
    {
        return &m_pWin;
    }
    SDL_Window *const *operator&() const
    {
        return &m_pWin;
    }
    operator const sdl2_h::ptr_window &() const
    {
        return m_pWin;
    }
    operator sdl2_h::ptr_window &()
    {
        return m_pWin;
    }
};
} // namespace open_stg::sdl2
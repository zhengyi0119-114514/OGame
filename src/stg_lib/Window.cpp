#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <utility>

open_stg::sdl2_h::PtrWindow::PtrWindow(SDL_Window *pWin) : m_pWin(pWin)
{
}
open_stg::sdl2_h::PtrWindow::~PtrWindow() noexcept
{
    if (m_pWin != nullptr)
    {
        SDL_DestroyWindow(m_pWin);
    }
}
SDL_Window *open_stg::sdl2_h::ptr_window::Get() const
{
    return m_pWin;
}
open_stg::sdl2_h::PtrWindow::PtrWindow(open_stg::sdl2_h::PtrWindow &&ref) noexcept
{
    this->m_pWin = std::move(ref.m_pWin);
    ref.m_pWin = nullptr;
}
open_stg::sdl2_h::PtrWindow &open_stg::sdl2_h::PtrWindow::operator=(open_stg::sdl2_h::PtrWindow &&rsh) noexcept
{
    open_stg::sdl2_h::PtrWindow pWin{std::move(rsh)};
    this->Swap(rsh);
    return *this;
}
void open_stg::sdl2_h::PtrWindow::Swap(open_stg::sdl2_h::PtrWindow &r)
{
    std::swap(this->m_pWin, r.m_pWin);
}
const SDL_Window *open_stg::sdl2_h::PtrWindow::operator->() const
{
    return m_pWin;
}
SDL_Window *open_stg::sdl2_h::PtrWindow::operator->()
{
    return m_pWin;
}
const SDL_Window &open_stg::sdl2_h::PtrWindow::operator*() const
{
    return *m_pWin;
}
SDL_Window &open_stg::sdl2_h::PtrWindow::operator*()
{
    return *m_pWin;
}
open_stg::sdl2_h::PtrWindow::operator SDL_Window *() const noexcept
{
    return m_pWin;
}
namespace open_stg::sdl2_h
{
SDL_Window* ptr_window::get() const
{
    return Get();
}
SDL_Window* ptr_window::data() const
{
    return Get();
}
SharedPtrWindow::SharedPtrWindow(SDL_Window *pWin) : m_spWin(std::make_shared<PtrWindow>(pWin))
{
}
void SharedPtrWindow::Swap(SharedPtrWindow& o) noexcept
{
    std::swap(this->m_spWin, o.m_spWin);
}
void SharedPtrWindow::swap(SharedPtrWindow& o) noexcept
{
    Swap(o);
}
SDL_Window& SharedPtrWindow::operator*()
{
    return const_cast<SDL_Window&>(*std::as_const(*this));
}
SDL_Window& SharedPtrWindow::operator*() const
{
    return *(m_spWin->get());
}
SDL_Window* SharedPtrWindow::Get() const noexcept
{
    return data();
}
SDL_Window* SharedPtrWindow::get() const noexcept
{
    return data();
}
SDL_Window* SharedPtrWindow::data() const noexcept
{
    return m_spWin->data();
}
SharedPtrWindow::operator SDL_Window *()const noexcept
{
    return m_spWin->get();
}
} // namespace open_stg::sdl2_h
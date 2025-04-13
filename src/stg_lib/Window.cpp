#include "sdl2.hpp"
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
open_stg::sdl2_h::PtrWindow::PtrWindow(open_stg::sdl2_h::PtrWindow &&ref)
{
    this->m_pWin = std::move(ref.m_pWin);
    ref.m_pWin = nullptr;
}
open_stg::sdl2_h::PtrWindow &open_stg::sdl2_h::PtrWindow::operator=(open_stg::sdl2_h::PtrWindow &&rsh)
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
SDL_Window **open_stg::sdl2_h::PtrWindow::operator&()
{
    return &this->m_pWin;
}
SDL_Window *const *open_stg::sdl2_h::PtrWindow::operator&() const
{
    return &this->m_pWin;
}
open_stg::sdl2_h::PtrWindow::operator SDL_Window *() const noexcept
{
    return m_pWin;
}

#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <utility>
namespace open_stg::sdl2_h
{
PtrSurface::PtrSurface(SDL_Surface *pSurf) : m_pSurf(pSurf)
{
}
PtrSurface::PtrSurface(PtrSurface && other)
{
    this->m_pSurf = other.m_pSurf;
    other.m_pSurf = NULL;
}
PtrSurface &PtrSurface::operator=(PtrSurface && other) noexcept
{
    PtrSurface s{std::move(other)};
    this->swap(s);
    return *this;
}
PtrSurface::~PtrSurface() noexcept
{
    if (m_pSurf != nullptr)
    {
        SDL_FreeSurface(m_pSurf);
    }
}
void ptr_surface::Swap(PtrSurface &ref)
{
    std::swap(this->m_pSurf, ref.m_pSurf);
}
SDL_Surface &ptr_surface::operator*()
{
    return *m_pSurf;
}
SDL_Surface *ptr_surface::operator->()
{
    return m_pSurf;
}
const SDL_Surface *ptr_surface::operator->() const
{
    return m_pSurf;
}
SDL_Surface *ptr_surface::Get() const
{
    return  m_pSurf;;
}
} // namespace open_stg::sdl2_h

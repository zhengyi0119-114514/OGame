
#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <utility>
namespace open_stg::sdl2_h
{
PtrSurface::PtrSurface(SDL_Surface *pSurf) : m_pSurf(pSurf)
{
}
PtrSurface::PtrSurface(PtrSurface && other) noexcept
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
SDL_Surface *ptr_surface::get() const
{
    return Get();
}
SDL_Surface *ptr_surface::data()const
{
    return Get();
}
} // namespace open_stg::sdl2_h

namespace open_stg::sdl2_h
{
SharedPtrSurface::SharedPtrSurface(SDL_Surface* pSurf) : 
    m_spSurf(std::make_shared<PtrSurface>(pSurf))
{
}

void SharedPtrSurface::Swap(SharedPtrSurface& o) noexcept
{
    std::swap(m_spSurf, o.m_spSurf);
}

void SharedPtrSurface::swap(SharedPtrSurface& o) noexcept
{
    Swap(o);
}

SDL_Surface& SharedPtrSurface::operator*()
{
    return const_cast<SDL_Surface&>(*std::as_const(*this));
}

SDL_Surface& SharedPtrSurface::operator*() const
{
    return *(m_spSurf->get());
}

SDL_Surface* SharedPtrSurface::operator->()
{
    return m_spSurf->get();
}

const SDL_Surface* SharedPtrSurface::operator->() const
{
    return m_spSurf->get();
}

SDL_Surface* SharedPtrSurface::Get() const noexcept
{
    return m_spSurf->get();
}

SDL_Surface* SharedPtrSurface::get() const noexcept
{
    return m_spSurf->get();
}

SDL_Surface* SharedPtrSurface::data() const noexcept
{
    return m_spSurf->get();
}

SharedPtrSurface::operator SDL_Surface*() const noexcept
{
    return m_spSurf->get();
}
} // namespace open_stg::sdl2_h

#include "sdl.hpp"
#include <utility>
namespace open_stg::sdl2_h
{
ptr_texture::PtrTexture(SDL_Texture *pTex)
{
    m_pTex = pTex;
}

PtrTexture::PtrTexture(PtrTexture &&other) noexcept
{
    this->swap(other);
}
void PtrTexture::Swap(PtrTexture &other)
{
    std::swap(this->m_pTex, other.m_pTex);
}
PtrTexture::~PtrTexture() noexcept
{
    if (m_pTex != nullptr)
    {
        SDL_DestroyTexture(m_pTex);
    }
}
const SDL_Texture &PtrTexture::operator*() const
{
    return *m_pTex;
}
SDL_Texture &PtrTexture::operator*()
{
    return *m_pTex;
}
PtrTexture::operator SDL_Texture *() const noexcept
{
    return m_pTex;
}
SDL_Texture *PtrTexture::Get() const
{
    return m_pTex;
}
SDL_Texture *ptr_texture::get() const
{
    return Get();
}
SDL_Texture *ptr_texture::data()const
{
    return Get();
}
} // namespace open_stg::sdl2_h

namespace open_stg::sdl2_h
{
SharedPtrTexture::SharedPtrTexture(SDL_Texture *pTex) : m_spTex(std::make_shared<PtrTexture>(pTex))
{
}

void SharedPtrTexture::Swap(SharedPtrTexture &o) noexcept
{
    std::swap(m_spTex, o.m_spTex);
}

void SharedPtrTexture::swap(SharedPtrTexture &o) noexcept
{
    Swap(o);
}

SDL_Texture &SharedPtrTexture::operator*()
{
    return *(m_spTex->get());
}

SDL_Texture &SharedPtrTexture::operator*() const
{
    return *(m_spTex->get());
}

SDL_Texture *SharedPtrTexture::operator->()
{
    return m_spTex->get();
}

const SDL_Texture *SharedPtrTexture::operator->() const
{
    return m_spTex->get();
}

SDL_Texture *SharedPtrTexture::Get() const noexcept
{
    return m_spTex->get();
}

SDL_Texture *SharedPtrTexture::get() const noexcept
{
    return m_spTex->get();
}

SDL_Texture *SharedPtrTexture::data() const noexcept
{
    return m_spTex->get();
}

SharedPtrTexture::operator SDL_Texture *() const noexcept
{
    return m_spTex->get();
}
} // namespace open_stg::sdl2_h

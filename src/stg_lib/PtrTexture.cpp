#include "sdl.hpp"
namespace open_stg::sdl2_h
{
	ptr_texture::PtrTexture(SDL_Texture* pTex)
	{
        m_pTex = pTex;
    }
    
    PtrTexture::PtrTexture(PtrTexture&& other)
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
    const SDL_Texture& PtrTexture::operator*() const
    {
        return *m_pTex;
    }
    SDL_Texture& PtrTexture::operator*()
    {
        return *m_pTex;
    }
    SDL_Texture* const* PtrTexture::operator&() const
    {
        return &m_pTex;
    }
    SDL_Texture** PtrTexture::operator&()
    {
        return &m_pTex;
    }
    PtrTexture::operator SDL_Texture* ()const noexcept
    {
        return m_pTex;
    }
    SDL_Texture* PtrTexture::Get() const
    {
        return m_pTex;
    }
}

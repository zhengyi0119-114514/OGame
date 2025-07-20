#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <utility>

namespace open_stg::sdl2_h
{
PtrRenderer::PtrRenderer(SDL_Renderer *pRend)
{
    this->m_pRend = pRend;
}
PtrRenderer::PtrRenderer(PtrRenderer &&r) noexcept
{
    std::swap(this->m_pRend, r.m_pRend);
}
PtrRenderer &PtrRenderer::operator=(PtrRenderer &&rsh) noexcept
{
    PtrRenderer rend{std::move(rsh)};
    this->Swap(rsh);
    return *this;
}
void PtrRenderer::Swap(PtrRenderer &ref)
{
    std::swap(this->m_pRend, ref.m_pRend);
}
PtrRenderer::~PtrRenderer() noexcept
{
    if (this->m_pRend != nullptr)
    {
        SDL_DestroyRenderer(this->m_pRend);
    }
}
PtrRenderer::operator SDL_Renderer *() const noexcept
{
    return this->Get();
}
SDL_Renderer &ptr_renderer::operator*()
{
    return *m_pRend;
}
const SDL_Renderer &ptr_renderer::operator*() const
{
    return *m_pRend;
}
SDL_Renderer *ptr_renderer::operator->()
{
    return m_pRend;
}
const SDL_Renderer *ptr_renderer::operator->() const
{
    return m_pRend;
}
SDL_Renderer *ptr_renderer::Get() const
{
    return m_pRend;
}

SDL_Renderer *ptr_renderer::data() const
{
    return Get();
}

SDL_Renderer *ptr_renderer::get() const
{
    return Get();
}
} // namespace open_stg::sdl2_h

namespace open_stg::sdl2_h
{
SharedPtrRenderer::SharedPtrRenderer(SDL_Renderer* pRend) : 
    m_spRend(std::make_shared<PtrRenderer>(pRend)) 
{
}

void SharedPtrRenderer::Swap(SharedPtrRenderer& o) noexcept
{
    std::swap(m_spRend, o.m_spRend);
}

void SharedPtrRenderer::swap(SharedPtrRenderer& o) noexcept
{
    Swap(o);
}

SDL_Renderer& SharedPtrRenderer::operator*()
{
    return const_cast<SDL_Renderer&>(*std::as_const(*this));
}

SDL_Renderer& SharedPtrRenderer::operator*() const
{
    return *(m_spRend->get());
}

SDL_Renderer* SharedPtrRenderer::operator->()
{
    return m_spRend->get();
}

const SDL_Renderer* SharedPtrRenderer::operator->() const
{
    return m_spRend->get();
}

SDL_Renderer* SharedPtrRenderer::Get() const noexcept
{
    return m_spRend->get();
}

SDL_Renderer* SharedPtrRenderer::get() const noexcept
{
    return m_spRend->get();
}

SDL_Renderer* SharedPtrRenderer::data() const noexcept
{
    return m_spRend->get();
}

SharedPtrRenderer::operator SDL_Renderer*() const noexcept
{
    return m_spRend->get();
}
} // namespace open_stg::sdl2_h

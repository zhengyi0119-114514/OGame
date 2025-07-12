#include "sdl.hpp"
#include <SDL2/SDL.h>
#include <utility>

namespace open_stg::sdl2_h
{
PtrRenderer::PtrRenderer(SDL_Renderer *pRend)
{
    this->m_pRend = pRend;
}
PtrRenderer::PtrRenderer(PtrRenderer &&r)
{
    std::swap(this->m_pRend, r.m_pRend);
}
PtrRenderer &PtrRenderer::operator=(PtrRenderer &&rsh)
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

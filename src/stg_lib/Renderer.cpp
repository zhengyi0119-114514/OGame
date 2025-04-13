#include <sdl2.hpp>
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
PtrRenderer& PtrRenderer::operator=(PtrRenderer&& rsh)
{
    PtrRenderer rend {std::move(rsh)};
    this->Swap(rsh);
}
void PtrRenderer::Swap(PtrRenderer& ref)
{
    std::swap(this->m_pRend,ref.m_pRend);
}
} // namespace open_stg::sdl2_h

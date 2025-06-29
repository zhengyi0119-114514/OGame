#include "open_game.hpp"
import open_stg;
using namespace open_stg::math_h;
using namespace open_stg::math;
using namespace open_stg::sdl2_h;
namespace open_stg::view_h
{
image::image(sdl2_h::shared_ptr_surface pSurf)
{
    m_pSurf = pSurf;
}
image::image(opt_h::image_resource_pool &pool, std::string_view name)
{
    m_pSurf = pool.get_surface_form_name(name);
}
image::image(opt_h::image_resource_pool& pool, uint32_t id)
{
    m_pSurf = pool.get_surface_form_id(id);
}
rectangles image::get_size()
{
    rectangles r{{SIZE_POINTLESS,SIZE_POINTLESS},0,0};
    r.height = m_pSurf->h;
    r.width = m_pSurf->w;
    return r;
}
void image::print_to_renderer(SDL_Renderer *rend)
{
    ptr_texture tex = SDL_CreateTextureFromSurface(rend, m_pSurf);
    SDL_Rect rect{0,0, m_pSurf->w, m_pSurf->h};
    SDL_Rect to_rect{(int)m_position.x, (int)m_position.y, (int)m_pSurf->w , (int)m_pSurf->h};
    SDL_RenderCopy(rend, tex, &rect,&to_rect);
}
void image::print_to_renderer_ex(SDL_Renderer* rend, rectangles r)
{
    ptr_texture tex = SDL_CreateTextureFromSurface(rend, m_pSurf);
    SDL_Rect rect{m_pSurf->w, m_pSurf->h, m_pSurf->w, m_pSurf->h};
    SDL_Rect to_rect{(int)m_position.x, (int)m_position.y, (int)m_pSurf->w, (int)m_pSurf->h};
    if (r.width < math_h::SIZE_UNDEFINED)
    {
        to_rect.w = r.width;
    }
    if (r.height < SIZE_UNDEFINED)
    {
        to_rect.h = r.height;
    }
    SDL_RenderCopy(rend, tex, &rect, &to_rect);
}
point image::get_position()
{
    return m_position;
}
}
#include "open_game.hpp"
using namespace open_stg::sdl2_h;
using namespace open_stg::opt_h;
namespace open_stg::view_h
{
static_wallpeaper::static_wallpeaper(shared_ptr_surface pSurf, math_h::rectangles screenSize)
    : image(pSurf), m_screenSize(screenSize)
{
    m_position = {0, 0};
}
static_wallpeaper::static_wallpeaper(image_resource_pool &p, std::string_view n, math_h::rectangles screenSize)
    : m_screenSize(screenSize), image(p, n)
{
}
static_wallpeaper::static_wallpeaper(image_resource_pool &pool, uint32_t id, math_h::rectangles screenSize)
    : m_screenSize(screenSize), image(pool, id)
{
}
math_h::rectangles static_wallpeaper::get_size()
{
    return math_h::rectangles{math_h::point{0, 0}, m_screenSize.width, m_screenSize.height};
}
void static_wallpeaper::set_screen_size(math_h::rectangles r)
{
    m_screenSize.width = r.width;
    m_screenSize.height = r.height;
}
math_h::point static_wallpeaper::get_position()
{
    return {0, 0};
}
void static_wallpeaper::print_to_renderer(SDL_Renderer *rend)
{
    image::print_to_renderer_ex(rend, {{0, 0}, m_screenSize.width, m_screenSize.height});
}
void static_wallpeaper::print_to_renderer_ex(SDL_Renderer* rend,math_h::rectangles)
{
    this->print_to_renderer(rend);
}
} // namespace open_stg::view_h
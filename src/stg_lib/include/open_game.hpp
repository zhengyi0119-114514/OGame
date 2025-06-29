#include "error_h.hpp"
#include "og_math_h.hpp"
#include "og_task_h.hpp"
#include "options.hpp"
#include "sdl.hpp"
#include "sdl_ttf.hpp"
#include <string>

#ifndef OGAME_STGLIB_H
#define OGAME_STGLIB_H 1

namespace open_stg
{
namespace mod_h
{
class ogame_obj
{
  public:
  private:
};
} // namespace mod_h
namespace view_h
{
class view_obj_pool
{
  public:

  private:

};

class view_obj
{
  public:
    virtual void print_to_renderer(SDL_Renderer *rend) = 0;
};

class image : public view_obj
{
  public:
    virtual void print_to_renderer(SDL_Renderer *rend) override;
    virtual void print_to_renderer_ex(SDL_Renderer *rend,
                                      math_h::rectangles to = {{math_h::SIZE_POINTLESS, math_h::SIZE_POINTLESS},
                                                               math_h::SIZE_UNDEFINED,
                                                               math_h::SIZE_UNDEFINED});
    image(sdl2_h::shared_ptr_surface pSurf);
    image(opt_h::image_resource_pool &pool, std::string_view name);
    image(opt_h::image_resource_pool &pool, uint32_t id);
    math_h::rectangles get_size();
    math_h::point get_position();

  protected:
    sdl2_h::shared_ptr_surface m_pSurf{nullptr};
    math_h::point m_position{};
};
class static_wallpeaper : image
{
  public:
    static_wallpeaper(sdl2_h::shared_ptr_surface pSurf, math_h::rectangles screenSize);
    static_wallpeaper(opt_h::image_resource_pool &pool, std::string_view name, math_h::rectangles screenSize);
    static_wallpeaper(opt_h::image_resource_pool &pool, uint32_t id, math_h::rectangles screenSize);
    void set_screen_size(math_h::rectangles r);
    math_h::rectangles get_size();
    math_h::point get_position();
    virtual void print_to_renderer(SDL_Renderer *rend) override;
    virtual void print_to_renderer_ex(SDL_Renderer *rend,
                                      math_h::rectangles pointless = {
                                          math_h::point{math_h::SIZE_POINTLESS, math_h::SIZE_POINTLESS},
                                          math_h::SIZE_POINTLESS, math_h::SIZE_POINTLESS}) override;

  private:
    math_h::rectangles m_screenSize{
        {math_h::SIZE_POINTLESS, math_h::SIZE_POINTLESS}, math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED};
};
} // namespace view_h
std::string InitOG_h(bool &bOk);
} // namespace open_stg
#endif // !OGAME_STGLIB_H

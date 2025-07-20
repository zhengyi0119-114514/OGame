/**
 * @file open_game.hpp
 * @author IceThorn
 * @brief 
 * @date 2025-07-19
 * 
 * @copyright :(
 * 
 */
#ifndef OGAME_STGLIB_H
#define OGAME_STGLIB_H 1

#include "error_h.hpp"
#include "og_math_h.hpp"
#include "og_task_h.hpp"
#include "options.hpp"
#include "sdl.hpp"
#include "sdl_ttf.hpp"
#include <string>
namespace open_stg
{
class applaction
{
};
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
/**
 * @brief [一个简单的基类,其派生类存储💾着图像，音频，动画等视图内容]
 */
class view_obj
{
  public:
    virtual ~view_obj() noexcept = default;
};
class graphs_object :public view_obj
{
    public:
    virtual void print_to_renderer(SDL_Renderer*rend) =0;
};
class image : public graphs_object
{
  public:
    virtual void print_to_renderer(SDL_Renderer *rend) override;
    virtual void print_to_renderer_ex(SDL_Renderer *rend,
                                      math_h::rectangles to = {
                                          math_h::point{math_h::SIZE_POINTLESS, math_h::SIZE_POINTLESS},
                                          math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED});
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
    /**
     * @brief Get the position of object
     * 
     * @return math_h::point !!Always return [0,0]
     */
    math_h::point get_position();
    virtual void print_to_renderer(SDL_Renderer *rend) override;
    /**
     * @brief !! Same as print_to_renderer
     * 
     * @param rend 
     * @param pointless 
     */
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

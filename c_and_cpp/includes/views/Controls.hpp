#include "modules/math.hpp"
#include "Surface.hpp"
#include <SDL2/SDL.h>

#ifndef OGAME_HEAD_VIEWS_CONTROLS
#define OGAME_HEAD_VIEWS_CONTROLS
namespace ogame::views
{
class IControl
{
  public:
    using CallBack = void (*)();
    virtual void OnClick(const ogame::math::Point &p);
    virtual void Display(SDL_Renderer *pRenderer) = 0;
    virtual ~IControl() = default;
};
class Button : public virtual IControl
{
  public:
    explicit Button(ogame::math::Rectangle r);
    virtual void Display(SDL_Renderer *pRenderer) override;

  private:
    sdlSurface m_surface;
};
} // namespace ogame::views
#endif

#include "modules/math.hpp"
#include <SDL2/SDL.h>

#ifndef OGAME_HEAD_VIEWS_CONTROLS
#define OGAME_HEAD_VIEWS_CONTROLS
namespace ogame::views
{
class IControl
{
    using CallBack = void (*)();
    virtual void Display(SDL_Renderer *pRenderer) = 0;
    virtual ~IControl() = default;
};
class Button : public virtual IControl
{
  public:
    explicit Button(ogame::math::Rectangle r);

  private:
    
};
} // namespace ogame::views
#endif
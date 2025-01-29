#pragma once
#include "Errors.hpp"
#include <SDL_surface.h>
namespace OGame::Views::Controls
{
class IWindowControl : public virtual OGame::OGameObject
{
  public:
    virtual void Display(SDL_Surface *&surface) const = 0;
};
} // namespace OGame::Views::Controls
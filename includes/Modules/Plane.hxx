#pragma once
#include "Math.hh"
#include <SDL_surface.h>

namespace OGame::Modules
{
class SelfPlane
{
  private:
    Math::Point m_Position;
    SDL_Surface m_SelfPlaneSuface;

  public:
    SelfPlane(Math::Point position):m_Position(position) {}
    Math::Point& PlanePosition() {return this->m_Position;}
    const Math::Point& PlanePosition() const {return this->m_Position;}
};
} // namespace OGame::Modules
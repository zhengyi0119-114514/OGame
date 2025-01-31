#pragma once
#include "Math.hh"

namespace OGame::Modules
{
class SelfPlane
{
  private:
    Math::Point m_Position;

  public:
    SelfPlane(Math::Point position):m_Position(position) {}
    Math::Point& PlanePosition() {return this->m_Position;}
    const Math::Point& PlanePosition() const {return this->m_Position;}
};
} // namespace OGame::Modules
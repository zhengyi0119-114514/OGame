#pragma once
#include <SDL_stdinc.h>
#include <cstdint>
namespace OGame::Modules::Math
{
class Point
{
  private:
    int32_t m_X;
    int32_t m_Y;

  public:
    Point(int32_t x,int32_t y) noexcept :m_X(x),m_Y(y){}
    int32_t GetX() const noexcept {return m_X;}
    int32_t GetY() const noexcept {return m_Y;}
    void SetX(int32_t x) {this->m_X=x;}
    void SetY(int32_t y) {this->m_Y=y;}
};
} // namespace OGame::Modules::Math
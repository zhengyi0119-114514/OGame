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
    void SetX(int32_t x) noexcept {this->m_X=x;}
    void SetY(int32_t y) noexcept {this->m_Y=y;}
};
class Rectangle
{
  private:
    uint32_t m_Width;
    uint32_t m_Hight;  
  public:
    Rectangle(uint32_t width,uint32_t hight) noexcept :m_Hight(hight),m_Width(width){}
    uint32_t GetWidth() const noexcept {return m_Width;}
    uint32_t GetHight() const noexcept {return m_Hight;}
    void SetWidth(uint32_t width) noexcept {this->m_Width = width;}
    void SetHight(uint32_t hight) noexcept {this->m_Hight = hight;}
};
class Circle
{
  private: 
    OGame::Modules::Math::Point m_Center;
    uint32_t m_Radius;
  public:
    Circle(OGame::Modules::Math::Point center,uint32_t radius) 
        noexcept : m_Radius(radius),m_Center(center){}
    const OGame::Modules::Math::Point& GetCenter() const noexcept {return this->m_Center;}
    uint32_t GetRadius() const noexcept {return this->m_Radius;}
    void SetCenter(const OGame::Modules::Math::Point& center) noexcept {this->m_Center = center;}
    void SetRadius(uint32_t radius) noexcept {this->m_Radius = radius;}
};
} // namespace OGame::Modules::Math

#include "ogame_defines.hpp"
#include <stddef.h>
#include <stdint.h>
#include <string>

#ifndef OGAME_HEAD_MODULES_MATH
#define OGAME_HEAD_MODULES_MATH
namespace ogame::math
{
class OGAME_API_WIN32 Point
{
  private:
    int32_t m_x, m_y;

  public:
    Point(int32_t x, int32_t y);
    int32_t &X() noexcept;
    int32_t X() const noexcept;
    int32_t &Y() noexcept;
    int32_t Y() const noexcept;
};
class IShape
{
  public:
    virtual bool IsIn(const Point &p) const noexcept = 0;
};
class OGAME_API_WIN32 Circle : public virtual IShape
{
  private:
    Point m_center;
    uint32_t m_iRadius;

  public:
    Circle(const Point &p, uint32_t iRadius);
    const Point &Center() const noexcept;
    uint32_t &Radius() noexcept;
    uint32_t Radius() const noexcept;
    virtual bool IsIn(const Point &p) const noexcept override;
};
class OGAME_API_WIN32 Rectangle : public virtual IShape
{
  private:
    Point m_pCenter;
    uint32_t m_iWeight, m_iHeight;

  public:
    Rectangle(uint32_t iWeight, uint32_t iHeight, const Point &center);
    uint32_t &Weight() noexcept;
    uint32_t Weight() const noexcept;
    uint32_t &Height() noexcept;
    uint32_t Height() const noexcept;
    const Point &Center() const noexcept;
    virtual bool IsIn(const Point &p) const noexcept override;
};
class OGAME_API_WIN32 Line
{
  private:
    const Point m_form, m_to;

  public:
    Line(const Point &form, const Point to);
    const Point &Form() const noexcept;
    const Point &To() const noexcept;
};
bool OGAME_API IsCollide(const Circle &cLeft, const Circle &cRight);
} // namespace ogame::math
#endif
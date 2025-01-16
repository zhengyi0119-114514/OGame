#include <stddef.h>
#include <stdint.h>
#include "ogame_defines.hpp"
#ifndef OGAME_HEAD_MODULES_MATH
#define OGAME_HEAD_MODULES_MATH
namespace ogame::math
{
class Point
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
} // namespace ogame::math
#endif
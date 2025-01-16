#include "modules/math.hpp"
namespace ogame::math
{
Point::Point(int32_t x, int32_t y) : m_x{x}, m_y{y}
{
}
int32_t &Point::X() noexcept
{
    return ref_this.m_x;
}

int32_t &Point::Y() noexcept
{
    return ref_this.m_y;
}

int32_t Point::X() const noexcept
{
    return ref_this.m_x;
}
int32_t Point::Y() const noexcept
{
    return ref_this.m_y;
}

} // namespace ogame::math
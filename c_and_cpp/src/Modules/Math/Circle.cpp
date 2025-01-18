#define OGAME_EXPORT
#include "modules/math.hpp"
#include <format>
#include <math.h>
#include <string>

namespace ogame::math
{
Circle::Circle(const Point &p, uint32_t iRadius) : m_center{p}, m_iRadius{iRadius}
{
}
const Point &Circle::Center() const noexcept
{
    return ref_this.m_center;
}
uint32_t &Circle::Radius() noexcept
{
    return ref_this.m_iRadius;
}
uint32_t Circle::Radius() const noexcept
{
    return ref_this.m_iRadius;
}
bool Circle::IsIn(const Point &p) const noexcept
{
    double dDistance = 0;
    dDistance =
        sqrt(static_cast<double>(pow(ref_this.Center().X() - p.X(), 2) + pow(ref_this.Center().Y() - p.Y(), 2)));
    return dDistance <= ref_this.Radius();
}
} // namespace ogame::math
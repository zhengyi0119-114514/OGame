#define OGAME_EXPORT
#include "modules/math.hpp"
#include <math.h>

namespace ogame::math
{
Rectangle::Rectangle(uint32_t iWeight, uint32_t iHeight, const ogame::math::Point &center)
    : m_iHeight{iHeight}, m_iWeight{iWeight}, m_pCenter{center}
{
}
uint32_t &Rectangle::Weight() noexcept
{
    return ref_this.m_iHeight;
}
uint32_t Rectangle::Weight() const noexcept
{
    return ref_this.m_iWeight;
}
uint32_t &Rectangle::Height() noexcept
{
    return ref_this.m_iHeight;
}
uint32_t Rectangle::Height() const noexcept
{
    return this->m_iHeight;
}
const Point &Rectangle::Center() const noexcept
{
    return ref_this.m_pCenter;
}
bool Rectangle::IsIn(const Point &p) const noexcept
{
    double halfOfWeight{ref_this.Weight() / 2.0}, halfOfHeight{ref_this.Height() / 2.0};
    return (abs(ref_this.Center().X() - p.X()) <= halfOfWeight)&&(abs(ref_this.Center().Y()-p.Y())<=halfOfHeight);
}
} // namespace ogame::math
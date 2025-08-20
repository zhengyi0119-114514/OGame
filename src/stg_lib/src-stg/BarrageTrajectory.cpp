#include "og.hpp"
namespace open_stg::stg
{
StraightLineTrajectory::StraightLineTrajectory(double theta, double r)
{
    m_2dvSpeed = {.x = r * math_h::Taylor7Cos(theta), .y = r * math_h::Taylor6Sin(theta)};
}
StraightLineTrajectory::StraightLineTrajectory(math_h::TwoDimensionalVector v)
{
    m_2dvSpeed = v;
}
void StraightLineTrajectory::Move(math_h::Point &p) const
{
    p.x += m_2dvSpeed.x;
    p.y += m_2dvSpeed.y;
}
} // namespace open_stg::stg
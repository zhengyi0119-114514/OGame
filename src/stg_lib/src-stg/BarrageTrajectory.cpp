#include "og.hpp"
namespace OpenGame::STG
{
StraightLineTrajectory::StraightLineTrajectory(double theta, double r) : m_dTheta(theta)
{
    m_2dvSpeed = {.x = r * Math::Taylor7Cos(theta), .y = r * Math::Taylor6Sin(theta)};
}
StraightLineTrajectory::StraightLineTrajectory(Math::TwoDimensionalVector v) : m_dTheta(atan2(v.y, v.x))
{
    m_2dvSpeed = v;
}
void StraightLineTrajectory::Move(Math::Point &p) const
{
    p.x += m_2dvSpeed.x;
    p.y += m_2dvSpeed.y;
}

double StraightLineTrajectory::GetDirection() const noexcept
{
    return m_dTheta;
}
} // namespace OpenGame::stg

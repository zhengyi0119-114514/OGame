#include "og.hpp"
namespace OpenGame::STG
{
bool CollisionDetection(const HitBox &l, const HitBox &r)
{
    if (Math::GetSquareDistanceBetweenTwoPoints(l.GetCenter(), r.GetCenter()) >
        Math::Power(l.GetRadius() + r.GetRadius(), 2))
    {
        return false;
    }
    for(const auto & p :l.GetCollisionDetectionPoints())
    {
        if(r.CollisionDetection(p))
            return true;
    }
    for(const auto& p:r.GetCollisionDetectionPoints())
    {
        if(l.CollisionDetection(p))
            return true;
    }
    return false;
}
} // namespace OpenGame::stg
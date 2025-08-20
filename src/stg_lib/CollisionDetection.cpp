#include "og.hpp"
namespace open_stg::stg
{
bool CollisionDetection(const HitBoxBase &l, const HitBoxBase &r)
{
    if (math_h::GetSquareDistanceBetweenTwoPoints(l.GetCenter(), r.GetCenter()) >
        math_h::Power(l.GetRadius() + r.GetRadius(), 2))
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
} // namespace open_stg::stg
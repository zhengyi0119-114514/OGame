#include "og_math_h.hpp"
namespace OpenGame::Math
{
CollisionDetectionPoints Circle::GetCollisionDetectionPoints() const
{
    int64_t radius{static_cast<int64_t>(this->radius)};
    double offset = radius * BAKA_CIRNO_NUMBER;
    return {
        Point{center.x - radius, center.y},          // ⬅️
        Point{center.x, center.y + radius},          // ⬆️
        Point{center.x + radius, center.y},          // ➡️
        Point{center.x, center.y - radius},          // ⬇️
        Point{center.x - offset, center.y + offset}, // ↖️
        Point{center.x + offset, center.y + offset}, // ↗️
        Point{center.x + offset, center.y - offset}, // ↘️
        Point{center.x - offset, center.y - offset}  // ↙️
    };
}
bool Circle::CollisionDetection(const Point &p) const
{
    return GetSquareDistanceBetweenTwoPoints(p, center) < Math::Power(radius, 2);
}
} // namespace OpenGame::Math
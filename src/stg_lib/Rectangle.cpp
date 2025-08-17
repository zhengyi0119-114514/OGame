#include "og_math_h.hpp"
namespace open_stg::math_h
{
CollisionDetectionPoints Rectangle::GetCollisionDetectionPoints() const
{
    int64_t width = this->width;
    int64_t height = this->height;
    int8_t iWidthHasOffset = width % 2;
    int8_t iHeightHasOffset = height % 2;
    return {
        Point{center.x - width / 2.0, center.y},                // ⬅️
        Point{center.x, center.y + height / 2.0},               // ⬆️
        Point{center.x + width / 2.0, center.y},                // ➡️
        Point{center.x, center.y - height / 2.0},               // ⬇️
        Point{center.x - width / 2.0, center.y + height / 2.0}, // ↖️
        Point{center.x + width / 2.0, center.y + height / 2.0}, // ↗️
        Point{center.x - width / 2.0, center.y - height / 2.0}, // ↙️
        Point{center.x + width / 2.0, center.y - height / 2.0}, // ↘️
    };
}
bool Rectangle::CollisionDetection(const Point &p) const
{
    if (IsUndefined())
    {
        return false;
    }

    int64_t halfWidth = width / 2;
    int64_t halfHeight = height / 2;

    int64_t left = center.x - halfWidth;
    int64_t right = center.x + halfWidth;
    int64_t top = center.y + halfHeight;
    int64_t bottom = center.y - halfHeight;

    return (p.x >= left && p.x <= right) && (p.y <= top && p.y >= bottom);
}
} // namespace open_stg::math_h
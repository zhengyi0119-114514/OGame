#include "og_math_h.hpp"
namespace OpenGame::Math
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

CollisionDetectionPoints RotatableRectangle::GetCollisionDetectionPoints() const
{
    if (rotationAngle == 0) {
        return Rectangle::GetCollisionDetectionPoints();
    }

    double cosTheta = Taylor7Cos(rotationAngle);
    double sinTheta = Taylor6Sin(rotationAngle);
    
    auto points = Rectangle::GetCollisionDetectionPoints();
    for (auto& p : points) {
        // Translate to origin
        double x = p.x - center.x;
        double y = p.y - center.y;
        
        // Apply rotation
        double rotatedX = x * cosTheta - y * sinTheta;
        double rotatedY = x * sinTheta + y * cosTheta;
        
        // Translate back
        p.x = rotatedX + center.x;
        p.y = rotatedY + center.y;
    }
    return points;
}

SDL_FRect RotatableRectangle::ToSdlFRect() const
{
    SDL_FRect rect = Rectangle::ToSdlFRect();
    // SDL_FRect doesn't have rotation field, so we just return basic rect
    // Rotation will be handled by renderer using separate rotation parameter
    return rect;
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
} // namespace OpenGame::Math

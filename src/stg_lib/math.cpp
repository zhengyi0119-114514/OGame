#include "og_math_h.hpp"
namespace open_stg::math_h
{
double GetDistanceBetweenTwoPoints(const Point &p1, const Point &p2)
{
    return sqrt(GetSquareDistanceBetweenTwoPoints(p1, p2));
}
double GetSquareDistanceBetweenTwoPoints(const Point &p1, const Point &p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
int DoubleToInt(double d)
{
    return (int)std::round(d);
}
SDL_FRect Rectangle::ToSdlFRect() const
{
    return SDL_FRect{static_cast<float>(center.x - width / 2), static_cast<float>(center.y + width / 2),
                     static_cast<float>(width), static_cast<float>(height)};
}

} // namespace open_stg::math_h

#include "og_math_h.hpp"
#include <algorithm>
#include <cstdint>

namespace open_stg::math_h
{

bool collide(const point &a, const point &b)
{
    return a.x == b.x && a.y == b.y;
}

bool collide(const point &p, const circle &c)
{
    uint32_t dx = p.x - c.center.x;
    uint32_t dy = p.y - c.center.y;
    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}

bool collide(const circle &c, const point &p)
{
    return collide(p, c);
}

bool collide(const point &p, const rectangles &r)
{
    return p.x >= r.top_left.x && p.x <= r.top_left.x + r.width && p.y >= r.top_left.y &&
           p.y <= r.top_left.y + r.height;
}

bool collide(const rectangles &r, const point &p)
{
    return collide(p, r);
}

bool collide(const circle &a, const circle &b)
{
    uint32_t dx = a.center.x - b.center.x;
    uint32_t dy = a.center.y - b.center.y;
    uint32_t distance_sq = dx * dx + dy * dy;
    uint32_t radius_sum = a.radius + b.radius;
    return distance_sq <= (radius_sum * radius_sum);
}

bool collide(const circle &c, const rectangles &r)
{
    uint32_t closestX = std::clamp(c.center.x, r.top_left.x, r.top_left.x + r.width);
    uint32_t closestY = std::clamp(c.center.y, r.top_left.y, r.top_left.y + r.height);

    uint32_t dx = c.center.x - closestX;
    uint32_t dy = c.center.y - closestY;
    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}

bool collide(const rectangles &r, const circle &c)
{
    return collide(c, r);
}

bool collide(const rectangles &a, const rectangles &b)
{
    return !(a.top_left.x + a.width < b.top_left.x || b.top_left.x + b.width < a.top_left.x ||
             a.top_left.y + a.height < b.top_left.y || b.top_left.y + b.height < a.top_left.y);
}

} // namespace open_stg::math_h

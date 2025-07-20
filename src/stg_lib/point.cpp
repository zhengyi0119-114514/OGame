#include "og_math_h.hpp"
#include <cstdint>
namespace open_stg::math_h
{
bool is_a_point_in_circle_h(point p, circle c)
{
    int32_t a = p.x - c.center.x;
    int32_t b = p.y - c.center.y;
    return a * a + b * b <= c.radius * c.radius;
}
bool is_a_point_in_rect_h(point p, rectangles r)
{
    return (p.x >= r.top_left.x && p.x <= r.top_left.x + r.width) &&
           (p.y >= r.top_left.y && p.y <= r.top_left.y + r.height);
}
} // namespace open_stg::math_h
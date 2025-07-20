#include "og_math_h.hpp"
#include <algorithm>
#include <cstdint>
namespace open_stg::math_h
{
bool is_intersecting_h(circle c, rectangles r)
{
    uint32_t closest_x = std::clamp(c.center.x, r.top_left.x, r.top_left.x + r.width);
    uint32_t closest_y = std::clamp(c.center.y, r.top_left.y, r.top_left.y + r.height);

    int32_t distance_x = (int32_t)c.center.x - closest_x;
    int32_t distance_y = (int32_t)c.center.y - closest_y;
    int32_t distance_squared = (distance_x*distance_x)+(distance_y*distance_y);
    return distance_squared <= (c.radius * c.radius);
}
} // namespace open_stg::math_h
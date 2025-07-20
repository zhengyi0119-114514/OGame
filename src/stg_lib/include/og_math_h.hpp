#ifndef OGAME_STGLIB_MATH_H
#define OGAME_STGLIB_MATH_H 1
#include <stdint.h>
namespace open_stg::math_h
{
constexpr static inline const uint32_t SIZE_UNDEFINED{114514};
constexpr static inline const uint32_t SIZE_POINTLESS{1919810};
struct point
{
    uint32_t x;
    uint32_t y;
};
struct vector
{
    uint32_t x;
    uint32_t y;
};
struct circle
{
    point center;
    uint32_t radius;
};
struct rectangles
{
    point top_left;
    uint32_t width;
    uint32_t height;
};
bool is_a_point_in_circle_h(point p,circle c);
bool is_a_point_in_rect_h(point p,rectangles r);
bool is_intersecting_h(circle c,rectangles r);
} // namespace open_stg::math_h
#endif // !OGAME_STGLIB_H

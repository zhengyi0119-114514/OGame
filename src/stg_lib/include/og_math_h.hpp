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
struct size
{
    uint32_t width;
    uint32_t height;
};

// 碰撞检测函数声明
bool collide(const point &a, const point &b);
bool collide(const point &p, const circle &c);
bool collide(const circle &c, const point &p);
bool collide(const point &p, const rectangles &r);
bool collide(const rectangles &r, const point &p);
bool collide(const circle &a, const circle &b);
bool collide(const circle &c, const rectangles &r);
bool collide(const rectangles &r, const circle &c);
bool collide(const rectangles &a, const rectangles &b);

} // namespace open_stg::math_h
#endif // !OGAME_STGLIB_H

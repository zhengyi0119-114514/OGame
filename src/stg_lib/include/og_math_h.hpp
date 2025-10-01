/**
 * @file og_math_h.hpp
 * @author zhengyi0119
 * @brief Math utilities and geometric structures[数学工具和几何结构]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-10
 *
 * Contains:
 * - Factorial and power calculations[阶乘和幂运算]
 * - Trigonometric functions[三角函数]
 * - Geometric shapes (Point, Circle, Rectangle)[几何图形(点、圆、矩形)]
 * - Collision detection utilities[碰撞检测工具]
 */
#ifndef OGAME_STGLIB_MATH_H
#define OGAME_STGLIB_MATH_H 1
#include <SDL3/SDL.h>
#include <array>
#include <cmath>
#include <concepts>
#include <math.h>
#include <numbers>
#include <stdint.h>


// Define π constant if not available[如果不可用则定义π常量]

namespace OpenGame::Math
{
// Compile-time trigonometric functions[编译时三角函数]
// Factorial calculation (!VALUE)[阶乘计算]
template <uint32_t N, typename TType = uint64_t>
    requires std::signed_integral<TType> || std::unsigned_integral<TType> || std::integral<TType> ||
             std::floating_point<TType>
struct Factorial
{
    static constexpr const inline TType VALUE = N * Factorial<N - 1, TType>::VALUE;
};
//(!0 = 1)
template <typename TType>
    requires std::signed_integral<TType> || std::unsigned_integral<TType> || std::integral<TType> ||
             std::floating_point<TType>
struct Factorial<0, TType>

{
    static constexpr const inline TType VALUE = 1;
};
template <typename TType = uint32_t>
    requires std::signed_integral<TType> || std::unsigned_integral<TType> || std::integral<TType> ||
             std::floating_point<TType>
constexpr inline TType Power(TType x, uint32_t n)
{
    return n == 0 ? 1.0 : x * Power<TType>(x, n - 1);
}
template <typename TType = double>
    requires std::floating_point<TType>
constexpr inline TType Taylor6Sin(TType x)
{
    // 使用模运算将x限制在[-π, π]范围内
    x = x - 2 * std::numbers::pi * static_cast<int>(x / (2 * std::numbers::pi));
    if (x > std::numbers::pi)
        x -= 2 * std::numbers::pi;
    if (x < -std::numbers::pi)
        x += 2 * std::numbers::pi;

    // 泰勒展开前7项
    return x - Power<TType>(x, 3) / Factorial<3>::VALUE + Power<TType>(x, 5) / Factorial<5>::VALUE -
           Power<TType>(x, 7) / Factorial<7>::VALUE + Power<TType>(x, 9) / Factorial<9>::VALUE -
           Power<TType>(x, 11) / Factorial<11>::VALUE + Power<TType>(x, 13) / Factorial<13>::VALUE;
}
template <typename TType = double>
    requires std::floating_point<TType>
constexpr inline TType Taylor7Cos(TType x)
{
    x = x - 2 * std::numbers::pi * static_cast<int>(x / (2 * std::numbers::pi));
    if (x > std::numbers::pi)
        x -= 2 * std::numbers::pi;
    if (x < -std::numbers::pi)
        x += 2 * std::numbers::pi;

    return 1 - Power<TType>(x, 2) / Factorial<2>::VALUE + Power<TType>(x, 4) / Factorial<4>::VALUE -
           Power<TType>(x, 6) / Factorial<6>::VALUE + Power<TType>(x, 8) / Factorial<8>::VALUE -
           Power<TType>(x, 10) / Factorial<10>::VALUE + Power<TType>(x, 12) / Factorial<12>::VALUE -
           Power<TType>(x, 14) / Factorial<14>::VALUE;
}

constexpr static inline const int64_t SIZE_UNDEFINED{(9 * 9) * 1145141919810};
// This literal is used to fill meaningless fields (~~This is a stinky
// number~~)[这个字面值用于填充无意义的字段(~~这是一串散发着恶臭的数字~~)]
constexpr static inline const int64_t SIZE_UNMEANING{1'145'141'919'810'114};
// Wish you Cirno's wisdom ᗜˬᗜ ⑨：𝓫𝓪𝓴𝓪[祝你获得琪露诺的智慧]
constexpr static inline const double BAKA_CIRNO_NUMBER{Taylor7Cos<double>(std::numbers::pi / 4)};

struct Point
{
    double x;
    double y;
    constexpr inline bool IsUndefined() const
    {
        return x >= SIZE_UNDEFINED || y >= SIZE_UNDEFINED;
    }
};
double GetDistanceBetweenTwoPoints(const Point &p1, const Point &p2);
double GetSquareDistanceBetweenTwoPoints(const Point &p1, const Point &p2);
int DoubleToInt(double d);
struct TwoDimensionalVector
{
    double x;
    double y;
};
using CollisionDetectionPoints = std::array<Point, 8>;
struct Circle
{
    Point center;
    double radius;
    CollisionDetectionPoints GetCollisionDetectionPoints() const;
    constexpr inline Point Center() const
    {
        return center;
    }
    bool CollisionDetection(const Point &p) const;
};
/**
 * @brief Rectangle
 *
 */
struct Rectangle
{
    Point center;
    double width;
    double height;
    /**
     * @brief Default initializer - use it and it won't make a sound[使用默认初始化器一用一个不吱声]
     *
     * Initializes with undefined SIZE_UNDEFINED values[使用SIZE_UNDEFINED值初始化]
     */
    constexpr inline Rectangle() : center(), width(SIZE_UNDEFINED), height(SIZE_UNDEFINED)
    {
    }
    constexpr inline Rectangle(Point pCenter, uint64_t uWidth, uint64_t uHeight)
        : center(pCenter), width(uWidth), height(uHeight)
    {
    }
    constexpr inline Point Center() const
    {
        return center;
    }
    /**
     * @brief Get the Collision Detection Points object
     *
     * @return CollisionDetectionPoints
     */
    CollisionDetectionPoints GetCollisionDetectionPoints() const;
    constexpr inline bool IsUndefined() const
    {
        return center.IsUndefined() || (width >= SIZE_UNDEFINED || height >= SIZE_UNDEFINED);
    }
    bool CollisionDetection(const Point &p) const;
    SDL_FRect ToSdlFRect() const;
};

/**
 * @brief Rotatable Rectangle with angle support[可旋转矩形]
 *
 * Extends basic Rectangle with rotation capability[扩展基础矩形类添加旋转功能]
 */
struct RotatableRectangle : public Rectangle
{
    double rotationAngle; // in radians[以弧度表示]
    /**
     * @brief Get rotated collision detection points[获取旋转后的碰撞检测点]
     */
    CollisionDetectionPoints GetCollisionDetectionPoints() const;

    /**
     * @brief Rotate the rectangle by given angle[按给定角度旋转矩形]
     */
    constexpr inline void Rotate(double angle)
    {
        rotationAngle += angle;
        // Normalize angle to [0, 2π)
        rotationAngle = fmod(rotationAngle, 2 * std::numbers::pi);
        if (rotationAngle < 0)
        {
            rotationAngle += 2 * std::numbers::pi;
        }
    }

    /**
     * @brief Set absolute rotation angle[设置绝对旋转角度]
     */
    constexpr inline void SetRotation(double angle)
    {
        rotationAngle = angle;
        // Normalize angle to [0, 2π)
        rotationAngle = fmod(rotationAngle, 2 * std::numbers::pi);
        if (rotationAngle < 0)
        {
            rotationAngle += 2 * std::numbers::pi;
        }
    }

    /**
     * @brief Get current rotation angle[获取当前旋转角度]
     */
    constexpr inline double GetRotation() const
    {
        return rotationAngle;
    }

    /**
     * @brief [该函数无法正常使用]
     */
    SDL_FRect ToSdlFRect() const;
};
template<typename T = double>
struct Size
{
    T width;
    T height;
    constexpr inline bool IsUndefined() const noexcept
    {
        return (width >= SIZE_UNDEFINED) || (height >= SIZE_UNDEFINED);
    }
};
struct FloatSize
{
    float width;
    float height;
    constexpr inline bool IsUndefined() const noexcept
    {
        return true;
    }
};
} // namespace OpenGame::Math
#endif // !OGAME_STGLIB_H

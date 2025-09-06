module;  // 全局模块片段开始
#include "og_math_h.hpp"  // 必须在全局模块片段内
// 全局模块片段结束

export module OpenGame.math;  // 主模块接口声明
export namespace OpenGame::math
{
using vector = OpenGame::Math::TwoDimensionalVector;
using point = OpenGame::Math::Point;
using circle = OpenGame::Math::Circle;
} // namespace OpenGame::math

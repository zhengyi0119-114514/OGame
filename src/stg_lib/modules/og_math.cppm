module;  // 全局模块片段开始
#include "og_math_h.hpp"  // 必须在全局模块片段内
// 全局模块片段结束

export module open_stg.math;  // 主模块接口声明
export namespace open_stg::math
{
using vector = open_stg::math_h::vector;
using point = open_stg::math_h::point;
using rectangles = open_stg::math_h::rectangles;
using circle = open_stg::math_h::circle;
} // namespace open_stg::math

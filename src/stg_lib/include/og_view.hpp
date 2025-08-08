/**
 * @file og_view.hpp
 * @author your name (you@domain.com)
 * @brief MVVM 的视图部分
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef OGAME_STGLIB_VIEW_H
#define OGAME_STGLIB_VIEW_H 1

namespace open_stg::view_h
{
/**
 * @brief [一个简单的基类,其派生类存储💾着图像，音频，动画等视图内容]
 */
class view_obj
{
  public:
    virtual ~view_obj() noexcept = default;
};
} // namespace open_stg::view_h
#endif
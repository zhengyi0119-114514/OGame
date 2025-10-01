/**
 * @file og_view.hpp
 * @author ice_thorn
 * @brief MVVM View Component[MVVM 的视图部分]
 * @version Ciallo～(∠・ω< )⌒★
 * @date 2025-08-06
 *
 * Contains:
 * - Window and screen management[窗口和屏幕管理]
 * - Image output interfaces[图像输出接口]
 * - View object implementations[视图对象实现]
 */
#ifndef OGAME_STGLIB_VIEW_H
#define OGAME_STGLIB_VIEW_H 1
#include "og_macro.h"
#include "og_math_h.hpp"
#include "og_sdl3_h.hpp"
#include "og_templates_h.hpp"
#include <vector>

namespace OpenGame::View
{
enum class PositionCoordinateSystem
{
    ABSOLUTE_POSITION = 0,
    RELATIVE_TO_THE_PARENT_WIDGET = 1,
};
struct CoordinateOffset
{
    float OffsetX;
    float OffsetY;
};
OG_INTERFACE IWidget
{
    virtual double GetWidth() const = 0;
    virtual void SetWidth(double dValue) = 0;

    virtual double GetHeight() const = 0;
    virtual void SetHeight(double dValue) = 0;

    virtual bool IsFocusable() const noexcept = 0;
    virtual SDL_FRect GetClickDetectionBox() const = 0;
    virtual SDL_FPoint SetAbsolutePosition() = 0;
    virtual void SetPosition(const SDL_FPoint &p, PositionCoordinateSystem pcs) = 0;
    /**
     * @brief Get the Parent Widget object
     * @return IWidget* 无父控件(Window)时返回 nullptr
     */
    virtual IWidget *GetParentWidget() const noexcept = 0;
};
class Window final : IWidget
{
  private:
    Math::Size<int> m_sWindowSize{};
    SDL3::Window m_w;
    SDL3::Renderer m_r;
    std::vector<std::shared_ptr<IWidget>> m_vspChildrenWidgets;

  public:
    Window(SDL3::Window spWin);
    virtual double GetWidth() const override;
    virtual double GetHeight() const override;
    virtual void SetWidth(double dValue) override;
    virtual void SetHeight(double dValue) override;
    virtual bool IsFocusable() const noexcept override;
    virtual SDL_FRect GetClickDetectionBox() const override;
    virtual IWidget *GetParentWidget() const noexcept override;
    virtual SDL_FPoint SetAbsolutePosition() override;
    virtual void SetPosition(const SDL_FPoint &p, PositionCoordinateSystem pcs) override;
};

} // namespace OpenGame::View
#endif

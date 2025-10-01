#ifndef OG_STG_H
#define OG_STG_H 1
#include "og_macro.h"
#include "og_main.hpp"
#include "og_math_h.hpp"
#include "og_module.hpp"
#include "og_module_view_h.hpp"
#include <vector>

namespace OpenGame::STG
{
const constexpr static inline int32_t BAKA_CIRNO_GROUP{999'999'999};  /// < バカ⑨ (Baka Cirno)[笨蛋琪露诺]
const constexpr static inline int32_t AYACHI_NENE_GROUP{0x0d00'0721}; /// < 绫地宁宁****
const constexpr static inline int32_t ENTER_TEXT_HERE_GROUP{0};
const constexpr static inline int32_t PLAYER_SHIP_GROUP{1};
const constexpr static inline int32_t PLAYER_SHIP_BULLET_GROUP{2};
const constexpr static inline int32_t ENEMY_GROUP{3};
const constexpr static inline int32_t ENEMY_BULLET_GROUP{4};
const constexpr static inline int32_t ITEM_GROUP{5};

/**
 * @brief Base class for hit boxes[碰撞框基类]
 */
class HitBox
{
  public:
    virtual ~HitBox() noexcept = default; ///< Virtual destructor[虚析构函数]

    /**
     * @brief Get center point[获取中心点]
     * @return Math::Point Center coordinates[中心坐标]
     */
    virtual const Math::Point &GetCenter() const noexcept = 0;
    Math::Point &GetCenter() noexcept;

    /**
     * @brief Get collision radius[获取碰撞半径]
     * @return int64_t
     * @note [非传统意义上的半径，指代距离中心最远的碰撞判定点]
     *       [Not traditional radius, represents farthest collision detection point from center]
     */
    virtual int64_t GetRadius() const noexcept = 0;

    /**
     * @brief Get collision detection points[获取碰撞检测点]
     * @return Math::CollisionDetectionPoints
     */
    virtual Math::CollisionDetectionPoints GetCollisionDetectionPoints() const = 0;

    /**
     * @brief Check collision with point[检测与点的碰撞]
     * @param p Point to check[要检测的点]
     * @return bool True if collided[如果碰撞返回true]
     */
    virtual bool CollisionDetection(const Math::Point &p) const = 0;
};
/**
 * @brief Circle shaped hit box[圆形碰撞框]
 */
class CircleHitBox final : public HitBox
{
  private:
    Math::Circle m_shape{}; ///< Underlying circle shape[底层圆形形状]

  public:
    /**
     * @brief Construct a new Circle Hit Box object[构造圆形碰撞框]
     * @param pLocation Center location[中心位置]
     * @param uRadius Radius[半径]
     */
    constexpr inline CircleHitBox(Math::Point pLocation, uint64_t uRadius) : m_shape(pLocation, uRadius)
    {
    }

    constexpr inline virtual const Math::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }

    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_shape.radius;
    }

    /**
     * @brief Get collision detection points[获取碰撞检测点]
     * @return constexpr Math::CollisionDetectionPoints
     */
    inline virtual Math::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }

    /**
     * @brief Check collision with point[检测与点的碰撞]
     * @param p Point to check[要检测的点]
     * @return constexpr bool True if collided[如果碰撞返回true]
     */
     inline virtual bool CollisionDetection(const Math::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
    virtual ~CircleHitBox() noexcept;
};
class RectangleHitBox final : public HitBox
{
  private:
    Math::Rectangle m_shape;
    int64_t m_radius{};

  public:
    constexpr inline RectangleHitBox(Math::Rectangle r) : m_shape{r}
    {
        m_radius = static_cast<int64_t>(ceil(sqrt(Math::Power(r.width, 2) + Math::Power(r.height, 2)) / 2));
    }
    constexpr inline virtual const Math::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }
    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_radius;
    }
     inline virtual Math::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }
     inline bool CollisionDetection(const Math::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
};
class RotatableRectangleHitBox final : public HitBox
{
  private:
    Math::RotatableRectangle m_shape;
    int64_t m_radius{};

  public:
    constexpr inline RotatableRectangleHitBox(Math::RotatableRectangle r) : m_shape{r}
    {
        m_radius = static_cast<int64_t>(ceil(sqrt(Math::Power(r.width, 2) + Math::Power(r.height, 2)) / 2));
    }
    constexpr inline virtual const Math::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }
    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_radius;
    }
     inline virtual Math::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }
     inline bool CollisionDetection(const Math::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
    constexpr inline void SetRotation(double dAngle)
    {
        m_shape.SetRotation(dAngle);
    }
};
bool CollisionDetection(const HitBox &l, const HitBox &r);
template <typename TTrajectory>
concept CTrajectory = requires(const TTrajectory &t, Math::Point &p) {
    { t.Move(p) } -> std::same_as<void>;
    { t.GetDirection() } -> std::same_as<double>;
} && std::movable<TTrajectory> && std::copyable<TTrajectory>;
template <typename THitBox>
concept CHitBox =
    requires(const THitBox &hb, const Math::Point &p) {
        { hb.GetCenter() } noexcept -> std::same_as<const Math::Point &>;
        { hb.GetRadius() } noexcept -> std::same_as<int64_t>;
        { hb.GetCollisionDetectionPoints() } -> std::same_as<Math::CollisionDetectionPoints>;
        { hb.CollisionDetection(p) } -> std::same_as<bool>;
    } && std::movable<THitBox> && std::copyable<THitBox> && std::derived_from<THitBox, HitBox> &&
    std::destructible<THitBox>;
template <CTrajectory TTrajectory, CHitBox THitBox> class Bullet
{
  private:
    uint32_t m_uSelfGroup{ENTER_TEXT_HERE_GROUP};
    int32_t m_iTargetGroup;
    THitBox m_cHitBox;
    TTrajectory m_cTrajectory;

  protected:
  public:
    inline Bullet(THitBox hb, TTrajectory trajectory, int32_t iTargetGroup) : m_cHitBox(hb), m_cTrajectory(trajectory)
    {
    }
    inline const HitBox &GetHitBox() const noexcept
    {
        return m_cHitBox;
    }
    inline int32_t GetGroup() const noexcept
    {
        return m_uSelfGroup;
    }
    inline constexpr int32_t GetTargetGroup() const noexcept
    {
        return m_iTargetGroup;
    }
    inline void DoOperator()
    {
        m_cTrajectory.Move(m_cHitBox.GetCenter());
    }
    inline const Math::Point &GetLocation() const noexcept
    {
        return m_cHitBox.GetCenter();
    }
    inline double GetDirection() const noexcept
    {
        return m_cTrajectory.GetDirection();
    }
    inline bool IsInRange(const Math::Size<double> &s)
    {
        Math::Point c = m_cHitBox.GetCenter();
        return c.x < s.width && c.y < s.height;
    }
};

class StraightLineTrajectory
{
  private:
    Math::TwoDimensionalVector m_2dvSpeed;
    double m_dTheta;

  public:
    StraightLineTrajectory(Math::TwoDimensionalVector v);
    StraightLineTrajectory(double theta, double r);
    void Move(Math::Point &p) const;
    double GetDirection() const noexcept;
};
using StraightLineCircleBullet = Bullet<StraightLineTrajectory, CircleHitBox>;
using StraightLineRectangleBullet = Bullet<StraightLineTrajectory, RectangleHitBox>;
using StraightLineRotatableRectangleBellet = Bullet<StraightLineTrajectory, RotatableRectangleHitBox>;

} // namespace OpenGame::stg

#endif // OG_STG_H_HPP

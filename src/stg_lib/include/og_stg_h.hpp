#ifndef OG_STG_H
#define OG_STG_H 1
#include "og_math_h.hpp"
#include "og_module.hpp"
#include <memory>

namespace open_stg::stg
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
class HitBoxBase
{
  public:
    virtual ~HitBoxBase() noexcept = default; ///< Virtual destructor[虚析构函数]

    /**
     * @brief Get center point[获取中心点]
     * @return math_h::Point Center coordinates[中心坐标]
     */
    virtual const math_h::Point &GetCenter() const noexcept = 0;
    math_h::Point &GetCenter() noexcept;

    /**
     * @brief Get collision radius[获取碰撞半径]
     * @return int64_t
     * @note [非传统意义上的半径，指代距离中心最远的碰撞判定点]
     *       [Not traditional radius, represents farthest collision detection point from center]
     */
    virtual int64_t GetRadius() const noexcept = 0;

    /**
     * @brief Get collision detection points[获取碰撞检测点]
     * @return math_h::CollisionDetectionPoints
     */
    virtual math_h::CollisionDetectionPoints GetCollisionDetectionPoints() const = 0;

    /**
     * @brief Check collision with point[检测与点的碰撞]
     * @param p Point to check[要检测的点]
     * @return bool True if collided[如果碰撞返回true]
     */
    virtual bool CollisionDetection(const math_h::Point &p) const = 0;
};
/**
 * @brief Circle shaped hit box[圆形碰撞框]
 */
class CircleHitBox final : public HitBoxBase
{
  private:
    math_h::Circle m_shape{}; ///< Underlying circle shape[底层圆形形状]

  public:
    /**
     * @brief Construct a new Circle Hit Box object[构造圆形碰撞框]
     * @param pLocation Center location[中心位置]
     * @param uRadius Radius[半径]
     */
    constexpr inline CircleHitBox(math_h::Point pLocation, uint64_t uRadius) : m_shape(pLocation, uRadius)
    {
    }

    constexpr inline virtual const math_h::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }

    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_shape.radius;
    }

    /**
     * @brief Get collision detection points[获取碰撞检测点]
     * @return constexpr math_h::CollisionDetectionPoints
     */
    constexpr inline virtual math_h::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }

    /**
     * @brief Check collision with point[检测与点的碰撞]
     * @param p Point to check[要检测的点]
     * @return constexpr bool True if collided[如果碰撞返回true]
     */
    constexpr inline virtual bool CollisionDetection(const math_h::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
    virtual ~CircleHitBox() noexcept;
};
class RectangleHitBox final : public HitBoxBase
{
  private:
    math_h::Rectangle m_shape;
    int64_t m_radius{};

  public:
    constexpr inline RectangleHitBox(math_h::Rectangle r) : m_shape{r}
    {
        m_radius = static_cast<int64_t>(ceil(sqrt(math_h::Power(r.width, 2) + math_h::Power(r.height, 2)) / 2));
    }
    constexpr inline virtual const math_h::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }
    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_radius;
    }
    constexpr inline virtual math_h::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }
    constexpr inline bool CollisionDetection(const math_h::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
};
class RotatableRectangleHitBox final : public HitBoxBase
{
  private:
    math_h::RotatableRectangle m_shape;
    int64_t m_radius{};

  public:
    constexpr inline RotatableRectangleHitBox(math_h::RotatableRectangle r) : m_shape{r}
    {
        m_radius = static_cast<int64_t>(ceil(sqrt(math_h::Power(r.width, 2) + math_h::Power(r.height, 2)) / 2));
    }
    constexpr inline virtual const math_h::Point &GetCenter() const noexcept override
    {
        return m_shape.center;
    }
    constexpr inline virtual int64_t GetRadius() const noexcept override
    {
        return m_radius;
    }
    constexpr inline virtual math_h::CollisionDetectionPoints GetCollisionDetectionPoints() const override
    {
        return m_shape.GetCollisionDetectionPoints();
    }
    constexpr inline bool CollisionDetection(const math_h::Point &p) const override
    {
        return m_shape.CollisionDetection(p);
    }
    constexpr inline void SetRotation(double dAngle)
    {
        m_shape.SetRotation(dAngle);
    }
};
bool CollisionDetection(const HitBoxBase &l, const HitBoxBase &r);

class StgGameObjectOnScreen : public mod_h::IGameObject
{
  protected:
    int32_t m_uSelfGroup = ENTER_TEXT_HERE_GROUP;

  public:
    virtual const HitBoxBase &GetHitBox() const noexcept = 0;
    virtual const math_h::Point &GetLocation() const noexcept = 0;
    virtual int32_t GetGroup() const noexcept = 0;
    virtual void DoOperator() override = 0; /// < 周期性调用
    virtual ~StgGameObjectOnScreen() noexcept = default;
};
typedef std::shared_ptr<StgGameObjectOnScreen> SharedStgGameObject;
template <typename TTrajectory>
concept CTrajectory =
    std::movable<TTrajectory> && std::copyable<TTrajectory> && requires(const TTrajectory &t, math_h::Point &p) {
        { t.Move(p) } -> std::same_as<void>;
        { t.GetDirection() } -> std::same_as<double>;
    };
template <typename THitBox>
concept CHitBox = std::movable<THitBox> && std::copyable<THitBox> && std::derived_from<THitBox, HitBoxBase> &&
                  requires(const THitBox &hb, const math_h::Point &p) {
                      { hb.GetCenter() } noexcept -> std::same_as<const math_h::Point &>;
                      { hb.GetRadius() } noexcept -> std::same_as<int64_t>;
                      { hb.GetCollisionDetectionPoints() } -> std::same_as<math_h::CollisionDetectionPoints>;
                      { hb.CollisionDetection(p) } -> std::same_as<bool>;
                  };
template <CTrajectory TTrajectory, CHitBox THitBox> class Bullet final : StgGameObjectOnScreen
{
  private:
    using StgGameObjectOnScreen::m_uSelfGroup;
    int32_t m_iTargetGroup;
    THitBox m_cHitBox;
    TTrajectory m_cTrajectory;

  protected:
    double m_dDirection{};
    uint32_t m_iTextureId{0};

  public:
    inline Bullet(THitBox hb, TTrajectory trajectory, int32_t iTargetGroup) : m_cHitBox(hb), m_cTrajectory(trajectory)
    {
    }
    virtual const HitBoxBase &GetHitBox() const noexcept override
    {
        return m_cHitBox;
    }
    constexpr inline virtual int32_t GetGroup() const noexcept override
    {
        return m_uSelfGroup;
    }
    constexpr inline int32_t GetTargetGroup() const noexcept
    {
        return m_iTargetGroup;
    }
    virtual void DoOperator() override
    {
        m_cTrajectory.Move(m_cHitBox.GetCenter());
    }
    constexpr inline 
};
class StraightLineTrajectory
{
  private:
    math_h::TwoDimensionalVector m_2dvSpeed;

  public:
    StraightLineTrajectory(math_h::TwoDimensionalVector v);
    StraightLineTrajectory(double theta, double r);
    void Move(math_h::Point &p) const;
    double GetDirection() const noexcept;
};
class PlayerShip final : public StgGameObjectOnScreen
{
  public:
    virtual int32_t GetGroup() const noexcept override;
    virtual const HitBoxBase &GetHitBox() const noexcept override;
    virtual void DoOperator() override;
    virtual const math_h::Point &GetLocation() const noexcept override;
    virtual ~PlayerShip() noexcept = default;
};
class StgScreen final : public mod_h::GameScreen
{
  private:
    math_h::Size m_sScreenSize{};
    PlayerShip m_psPlayerShip;

  public:
    virtual void StartGame() override;
    virtual void StopGame() override;
    virtual void PauseGame() override;
    virtual void ContinueGame() override;
    virtual void HandleEvent(const SDL_Event &e) override;
    virtual math_h::Size GetScreenSize() const override;
};
} // namespace open_stg::stg

#endif // OG_STG_H_HPP

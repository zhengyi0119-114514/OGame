#ifndef OG_STG_H
#define OG_STG_H 1
#include "og_math_h.hpp"
#include "og_module.hpp"
#include "og_module_view_h.hpp"

namespace open_stg::stg
{
// バカ⑨ (Baka Cirno)[笨蛋琪露诺]
const constexpr static inline int32_t BAKA_CIRNO_GROUP{999'999'999};
const constexpr static inline int32_t AYACHI_NENE_GROUP{0x0d00'0721}; /// < 绫地宁宁****
const constexpr static inline int32_t PLAYER_SHIP_GROUP{1};
const constexpr static inline int32_t PLAYER_SHIP_BULLET_GROUP{2};
const constexpr static inline int32_t ENEMY_GROUP{3};
const constexpr static inline int32_t ENEMY_BULLET_GROUP{4};
const constexpr static inline int32_t ITEM_GROUP{5};
const constexpr static inline int32_t ENTER_TEXT_HERE_GROUP{0};

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
    virtual math_h::Point GetCenter() const noexcept = 0;

    /**
     * @brief Get collision radius[获取碰撞半径]
     * @return int64_t
     * @note [非传统意义上的半径，指代距离中心最远的碰撞判定点]
     *       [Not traditional radius, represents farthest collision detection point from center]
     */
    virtual int64_t GetRaduis() const noexcept = 0;

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

    constexpr inline virtual math_h::Point GetCenter() const noexcept override
    {
        return m_shape.Center();
    }

    constexpr inline virtual int64_t GetRaduis() const noexcept override
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
    constexpr inline bool CollisionDetection(const math_h::Point &p) const override
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
        m_radius = sqrt(math_h::Power(r.width, 2) + math_h::Power(r.height, 2)) / 2;
    }
    constexpr inline virtual math_h::Point GetCenter() const noexcept override
    {
        return m_shape.Center();
    }
    constexpr inline virtual int64_t GetRaduis() const noexcept override
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
bool CollisionDetection(const HitBoxBase &l, const HitBoxBase &r);

class StgGameObject : public mod_h::IGameObject
{
  protected:
    math_h::Point m_pLocation{math_h::SIZE_UNDEFINED, math_h::SIZE_UNDEFINED};
    int32_t m_uGroup = BAKA_CIRNO_GROUP;

  public:
    virtual const HitBoxBase &GetHitBox() const = 0;
    virtual int32_t GetGroup() const = 0;
};
class Bullet : public StgGameObject
{
  protected:
    math_h::TwoDimensionalVector m_2dvDisplacement{};
};

class GtgScreen : public mod_h::GameScreen
{
  private:
  public:
    virtual void StartGame() override;
};
} // namespace open_stg::stg

#endif // OG_STG_H_HPP

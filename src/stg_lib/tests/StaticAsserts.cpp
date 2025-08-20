#include "og.hpp"

using namespace open_stg::stg;

static_assert(CTrajectory<StraightLineBarrageTrajectory>);
static_assert(CHitBox<CircleHitBox>);
static_assert(CHitBox<RectangleHitBox>);
static_assert(CHitBox<RotatableRectangleHitBox>);
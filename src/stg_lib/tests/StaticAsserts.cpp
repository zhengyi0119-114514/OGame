#include "og.hpp"

using namespace OpenGame;
using namespace OpenGame::stg;
using namespace OpenGame::View;
StaticAssert(CTrajectory<StraightLineTrajectory>);
StaticAssert(CStgGameObject<Bullet<StraightLineTrajectory, CircleHitBox>>);
StaticAssert(CStgGameObject<PlayerShip>);
StaticAssert(CHitBox<CircleHitBox>);
StaticAssert(CHitBox<RectangleHitBox>);
StaticAssert(CHitBox<RotatableRectangleHitBox>);


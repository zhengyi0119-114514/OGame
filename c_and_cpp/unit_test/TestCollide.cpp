#include <catch2/catch_all.hpp>
#include "modules/math.hpp"

TEST_CASE("OGame.Modules.Math.Collde.Circle","[OGAME]")
{
    using namespace ogame;
    math::Circle c1{{0,0},2},c2{{0,3},1} ,c3{{0,5},1};
    REQUIRE(math::IsCollide(c1,c2));
    REQUIRE_FALSE(math::IsCollide(c1,c3));
}
#include <catch.hpp>
#include "modules/math.hpp"

TEST_CASE("Module.Modules.Math.Point","[OGAME]")
{
    ogame::math::Point p(10,11);
    REQUIRE(p.X() == 10);
    REQUIRE(p.Y() == 11);
    p.X() = 15;
    p.Y() = 19;
    REQUIRE(p.X()==15);
    REQUIRE(p.Y()==19);
}
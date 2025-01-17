#include "catch.hpp"
#include "modules/math.hpp"

TEST_CASE("OGame.Modules.Math.Circle", "[OGAME]")
{
    ogame::math::Circle c(ogame::math::Point(0, 0), 5);
    REQUIRE(c.IsIn(ogame::math::Point(4, 3)));
    REQUIRE(c.IsIn(ogame::math::Point(4, -3)));
    REQUIRE_FALSE(c.IsIn(ogame::math::Point(4, 4)));
    c = ogame::math::Circle({5, 5}, 5);
    REQUIRE(c.IsIn({0, 5}));
    REQUIRE(c.IsIn({5, 5}));
    REQUIRE_FALSE(c.IsIn({0, 6}));
}
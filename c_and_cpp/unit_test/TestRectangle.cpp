#include "modules/math.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("OGame.Modules.Math.Rectangle","[OGAME]")
{
    using namespace ogame;
    math::Rectangle r(50,50,{0,0});
    REQUIRE(r.IsIn({0,0}));
    REQUIRE(r.IsIn({25,0}));
    REQUIRE_FALSE(r.IsIn({50,0}));
    r =math::Rectangle(50,20,{0,0});
    REQUIRE(r.IsIn({25,10}));
    REQUIRE_FALSE(r.IsIn({26,10}));
}
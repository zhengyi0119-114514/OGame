#include "modules/math.hpp"
#include <catch2/catch_all.hpp>

TEST_CASE("OGame.Modules.Math.Line", "[OGAME]")
{
    using namespace ogame;
    math::Line l({10, 10}, {0, 0});
    REQUIRE(l.Form().X() == math::Point{10, 10}.X());
    REQUIRE(l.Form().Y() == math::Point{10, 10}.Y());
    REQUIRE(l.To().X() == math::Point{0, 0}.X());
    REQUIRE(l.To().Y() == math::Point{0, 0}.Y());
}
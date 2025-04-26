#include <catch.hpp>
#include <catch2/catch_test_macros.hpp>
#include "open_game.hpp"
TEST_CASE("test_init","[OGAME]")
{
    bool bOk = false;
    InitOG(bOk);
    REQUIRE(bOk);
}

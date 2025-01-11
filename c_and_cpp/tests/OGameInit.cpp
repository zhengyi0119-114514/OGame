#include "catch.hpp"
#include "modules.h"
TEST_CASE("OGameInitTest","[ogame_modules]")
{
    REQUIRE((OGameInit(null)==OGAME_ERROR_ARGUEMENT_IS_NULL));
}
#include "Modules/Config.hpp"
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
TEST_CASE("OGame.Test.Config.Path","[OGAME.CONFIG]")
{
    auto path = OGame::Config::GetConfigFileDirectory();
    OGame::Config::CreateDirectoryIfNotExists(path);
    REQUIRE(std::filesystem::exists(path));
}
#include "Resource.hh"
#include <Catch2/catch_all.hpp>
#include <Catch2/catch_test_macros.hpp>
#include <filesystem>
namespace fs = std::filesystem;
namespace rs = OGame::Resources;
TEST_CASE("OGame.Resource.CheckDirectory", "[OGAME.RESOURCE]")
{
    REQUIRE(fs::exists(rs::DataDirectory));
    REQUIRE(fs::exists(rs::ImageDirectory));
    REQUIRE(fs::exists(rs::FontsDirectory));
    REQUIRE(fs::exists(rs::LicenseDirectory));
    REQUIRE(fs::exists(rs::ConfigFileDirectory));
}
TEST_CASE("OGame.Resource.CheckFile", "[OGAME.RESOURCE]")
{
    REQUIRE(fs::exists(rs::SelfImage));
    REQUIRE(fs::exists(rs::CEFFontsCJK));
    REQUIRE(fs::exists(rs::CEFFontsCJKMono));
    REQUIRE(fs::exists(rs::FontsDirectory));
    REQUIRE(fs::exists(rs::SDL_imageLicense));
    REQUIRE(fs::exists(rs::SDL_ttfLicense));
    REQUIRE(fs::exists(rs::SDL2License));
    REQUIRE(fs::exists(rs::SDL2ppLicense));
    REQUIRE(fs::exists(rs::SpdlogLicense));
    REQUIRE(fs::exists(rs::Toml11License));
}

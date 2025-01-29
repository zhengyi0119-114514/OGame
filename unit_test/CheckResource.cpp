#include "Modules/Config.hpp"
#include <Catch2/catch_all.hpp>
#include <Catch2/catch_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <filesystem>

TEST_CASE("OGame.Resource.Check", "[OGAME.RESOURCE]")
{
    std::filesystem::path imagePath{std::filesystem::current_path() / "data" / "images"};
    std::filesystem::path fontsPath{std::filesystem::current_path() / "data" / "fonts"};
    std::filesystem::path licensePath(std::filesystem::current_path() /"data"/"licenses");

    // DIRECTORY
    REQUIRE(std::filesystem::exists(imagePath));
    REQUIRE(std::filesystem::exists(fontsPath));
    REQUIRE(std::filesystem::exists(licensePath));
    // IMAGES
    REQUIRE(std::filesystem::exists(imagePath/"self.png"));
    // FONT
    REQUIRE(std::filesystem::exists(fontsPath/"CEFFontsCJK-Regular.ttf"));
    REQUIRE(std::filesystem::exists(fontsPath/"CEFFontsCJKMono-Regular.ttf"));    
    // LICENSE
    REQUIRE(std::filesystem::exists(licensePath/"cef-fonts-cjk.license"));
    REQUIRE(std::filesystem::exists(licensePath/"sdl2.license"));
    REQUIRE(std::filesystem::exists(licensePath/"sdl2pp.license"));
    REQUIRE(std::filesystem::exists(licensePath/"sdl-image.license"));
    REQUIRE(std::filesystem::exists(licensePath/"sdl-ttf.license"));
    REQUIRE(std::filesystem::exists(licensePath/"spdlog.license"));
    REQUIRE(std::filesystem::exists(licensePath/"toml11.license"));
}
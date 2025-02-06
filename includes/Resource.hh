#pragma once
#include <SDL2/SDL_surface.h>
#include <SDL_ttf.h>
#include <filesystem>

namespace OGame::Resources
{
// directory
const std::filesystem::path DataDirectory{std::filesystem::current_path() / "data"};
const std::filesystem::path FontsDirectory{DataDirectory / "fonts"};
const std::filesystem::path ImageDirectory{DataDirectory / "images"};
const std::filesystem::path LicenseDirectory(DataDirectory / "licenses");
const std::filesystem::path ConfigFileDirectory{DataDirectory/"config"};

// files
const std::filesystem::path SelfImage{ImageDirectory / "self.png"};
// fonts
const std::filesystem::path CEFFontsCJK{FontsDirectory / "CEFFontsCJK-Regular.ttf"};
const std::filesystem::path CEFFontsCJKMono{FontsDirectory / "CEFFontsCJKMono-Regular.ttf"};
// licenses
const std::filesystem::path FontLicense(LicenseDirectory / "cef-fonts-cjk.license");
const std::filesystem::path SDL2License(LicenseDirectory / "sdl2.license");
const std::filesystem::path SDL2ppLicense{LicenseDirectory / "sdl2pp.license"};
const std::filesystem::path SDL_imageLicense{LicenseDirectory / "sdl-image.license"};
const std::filesystem::path SDL_ttfLicense{LicenseDirectory / "sdl-ttf.license"};
const std::filesystem::path SpdlogLicense{LicenseDirectory / "spdlog.license"};
const std::filesystem::path Toml11License{LicenseDirectory / "toml11.license"};
using GAME_RESOURCE = struct
{
    SDL_Surface* Self;
    TTF_Font* CEFFontsCJKFont;
    TTF_Font* CEFFontsCJKMonoFont;
};
void GetResources(GAME_RESOURCE& resource);
GAME_RESOURCE GetResources();
void FreeResource();
} // namespace OGame::Resources
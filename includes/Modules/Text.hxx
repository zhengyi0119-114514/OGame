#pragma once
#include "Resource.hh"
#include <filesystem>

namespace OGame::Resources::Text
{
using TEXT_RESOURCE = struct
{
    std::string Title;
};
const std::filesystem::path TextFile{Resources::ConfigFileDirectory / "Text.cfg"};
void InitText();
const TEXT_RESOURCE &GetText();
} // namespace OGame::Resources::Text
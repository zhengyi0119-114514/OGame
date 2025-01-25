#include "Modules/Config.hpp"
#include <filesystem>
#include <format>
#include <spdlog/spdlog.h>

int main(int argc, char **argv)
{
    spdlog::info("Hello world");
    auto path = OGame::Config::GetConfigFilePath();
    spdlog::info(std::format("Config file at {:}.", path.string()));
}
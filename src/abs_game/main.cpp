#if __has_include("safec.h")
#include <safec.h>
#endif
#define __STDC_WAND_LIB_EXT1__ 1
#include "og.hpp"
#include <SDL3/SDL.h>
#include <boost/program_options.hpp>
#include <format>
#include <spdlog/spdlog.h>
#include <stdlib.h>

// import OpenGame;
using namespace OpenGame::SDL3;
using namespace OpenGame::Math;
using namespace OpenGame::Option;
using namespace OpenGame::View;
using namespace OpenGame;
using namespace boost::program_options;

int main(int argc, char **args)
{
    InitOpenGame();
    std::filesystem::path pConfigFileDirectory{Option::GetProgramOptionFileDirectory()};
    SPDLOG_INFO(std::format("config file at {0:}", pConfigFileDirectory.string()));
    Clock<60> c;
    c.Init();
    QuitOpenGame();
}

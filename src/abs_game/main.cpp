#if __has_include("safec.h")
#include <safec.h>
#endif
#define __STDC_WAND_LIB_EXT1__ 1
#include "og.hpp"
#include <boost/program_options.hpp>
#include <spdlog/spdlog.h>
#include <format>
#include <stdlib.h>


// import open_stg;
using namespace open_stg::sdl3_h;
using namespace open_stg::math_h;
using namespace open_stg::opt_h;
using namespace open_stg;
using namespace boost::program_options;

int main(int argc, char **args)
{
    InitOpenGame();
    std::filesystem::path configFileDirectory{opt_h::GetProgramOptionFileDirectory()};
    SPDLOG_INFO(std::format("config file at {0:}",configFileDirectory.string()));
}
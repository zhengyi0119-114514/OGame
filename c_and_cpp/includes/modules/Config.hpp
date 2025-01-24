#include "ogame_defines.hpp"
#include <stdint.h>
#include <filesystem>

#ifndef OGAME_CONFIG
#define OGAME_CONFIG
namespace ogame::config
{
using CONFIG = struct
{
    uint32_t iWindowWidth;
    uint32_t iWindowHeight;
};
std::filesystem::path OGAME_API GetConfigFilePath();

} // namespace ogame::config
#endif
#define OGAME_EXPORT
#include "modules/Config.hpp"
#include <spdlog/spdlog.h>


namespace ogame::config
{

CONFIG OGAME_API GetDefaultConfig()
{
    return {720, 1280};
}
} // namespace ogame::config
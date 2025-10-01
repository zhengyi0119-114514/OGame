/**
 * @file options.hpp
 * @author IceThorn :(
 * @brief
 * @date 2025-07-19
 * :( :( 写这段的时候差点气死 🐎的
 */
#ifndef OGAME_STGLIB_OPT_H
#define OGAME_STGLIB_OPT_H
#include "og_templates_h.hpp"
#include "og_view.hpp"
#include <filesystem>

namespace OpenGame::Option
{
std::filesystem::path GetProgramOptionFileDirectory();
} // namespace OpenGame::Option
#endif
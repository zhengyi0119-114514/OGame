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
using SurfacePool = ObjectPool<sdl3_h::SharedPtrSurface>;
using TexturePool = ObjectPool<sdl3_h::SharedPtrTexture>;
using TtfFontPool = ObjectPool<sdl3_h::SharedPtrTtfFont>;
} // namespace OpenGame::Option
#endif
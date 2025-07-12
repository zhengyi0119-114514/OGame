#ifndef OGAME_LAUNCHER_API
#define OGAME_LAUNCHER_API 1
#include <string>
#include <vector>
#include <span>
#include <SDL2/SDL.h>
#undef main
std::vector<SDL_DisplayMode> GetAndSelectDisplayMode();
std::vector<std::string> DisplayModeToStringVectoy(std::span<SDL_DisplayMode> dms);
#endif
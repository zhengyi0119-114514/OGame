#include "og.hpp"
namespace OpenGame::sdl3_h
{
void WindowManager::DestoryObject(SDL_Window *p)
{
    if (p != nullptr)
    {
        SDL_DestroyWindow(p);
    }
}
} // namespace OpenGame::sdl3_h
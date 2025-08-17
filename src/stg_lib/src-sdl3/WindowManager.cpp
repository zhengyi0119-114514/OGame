#include "og.hpp"
namespace open_stg::sdl3_h
{
void WindowManager::DestoryObject(SDL_Window *p)
{
    if (p != nullptr)
    {
        SDL_DestroyWindow(p);
    }
}
} // namespace open_stg::sdl3_h
#include "views/windows.hpp"

namespace ogame::views
{
sdlWindow::~sdlWindow()
{
    SDL_DestroyWindow(this->m_pWindow);
}
sdlWindow::sdlWindow(SDL_Window *pWindow) : m_pWindow{pWindow}
{
}
sdlWindow::operator SDL_Window *() const
{
    return this->m_pWindow;
}
} // namespace ogame::views
#include "views/windows.hpp"
#include <utility>

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
void sdlWindow::AddSubControl(std::shared_ptr<IControl> c)
{
    this->m_controlsList.push_back(std::move(c));
}
} // namespace ogame::views

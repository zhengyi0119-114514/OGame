#include "og.hpp"
#include <ranges>
namespace OpenGame::View
{
double Window::GetWidth() const
{
    return m_w.GetSize().width;
}
double Window::GetHeight() const
{
    return RefThis.m_w.GetSize().height;
}
Window::Window(SDL3::Window pWin):m_w(std::move(pWin)),m_r(SDL_CreateRenderer(pWin.Get(), "defalut"))
{

}
} // namespace OpenGame::View

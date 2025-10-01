#include "og.hpp"
namespace OpenGame::SDL3
{
void Window::_DestroyObject(SDL_Window *)
{
    SDL_DestroyWindow(m_p);
}
Window::Window(std::string_view svTitle, int iWindowWidth, int iWindowHeight, WindowFlags wfFlag, Uint64 wfexFlag)
    : PtrSdlObjectTemplate<SDL_Window>(NullPtr)
{
    m_p = SDL_CreateWindow(svTitle.data(), iWindowWidth, iWindowHeight, StaticCast<Uint64>(wfFlag) | wfexFlag);
    if (!m_p)
    {
        throw Error::InitException(NameOf(PtrWindow), SDL_GetError());
    }
}
Math::Size<int> Window::GetSize() const
{
    int iWindowHeight, iWindowWidth;
    if (!SDL_GetWindowSize(Get(), &iWindowWidth, &iWindowHeight))
        throw Error::SDLException(NameOf(SDL_GetWindowSize));
    return {iWindowWidth, iWindowHeight};
}
void Window::SetSize(Math::Size<int> s)
{
    if (!SDL_SetWindowSize(Get(), s.width, s.height))
        throw Error::SDLException(NameOf(SDL_GetWindowSize));
}
SDL_WindowID Window::GetWindowID() const
{
    VAR wid = SDL_GetWindowID(m_p);
    if (!wid)
        throw Error::SDLException(NameOf(PtrWindow));
    return wid;
}
const char *Window::GetTitle() const
{
    return SDL_GetWindowTitle(RefThis.m_p);
}
Bool Window::IsKeyboardGrab() const
{
    return SDL_GetWindowKeyboardGrab(Get());
}
SDL_WindowFlags Window::GetFlags() const
{
    return SDL_GetWindowFlags(Get());
}
Math::Size<int> Window::GetSizeInPixels() const
{
    int iWindowHeight, iWindowWidth;
    if (!SDL_GetWindowSizeInPixels(Get(), &iWindowWidth, &iWindowHeight))
        throw Error::SDLException(NameOf(PtrWindow));
    return {iWindowWidth, iWindowHeight};
}
Window::~Window() noexcept
{
    _DestroyObject(Get());
}
Math::Size<int> Window::GetMaximumSize() const
{
    Math::Size<int> s;
    if (!SDL_GetWindowMaximumSize(Get(), &s.width, &s.height))
        throw Error::SDLException(NameOf(PtrWindow));
    return s;
}
void Window::SetMinimumSize(const Math::Size<int> s)
{
    if (!SDL_SetWindowMinimumSize(RefThis.Get(), s.width, s.height))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::SetMaximunSize(const Math::Size<int> s)
{
    if (!SDL_SetWindowMaximumSize(RefThis.Get(), s.width, s.height))
        throw Error::SDLException(NameOf(PtrWindow));
}
Math::Size<int> Window::GetMinimumSize() const
{
    Math::Size<int> s;
    if (!SDL_GetWindowMinimumSize(RefThis.Get(), &s.width, &s.height))
        throw Error::SDLException(NameOf(PtrWindow));
    return s;
}
SDL_Point Window::GetPosition() const
{
    SDL_Point p;
    if (!SDL_GetWindowPosition(Get(), &p.x, &p.y))
        throw Error::SDLException(NameOf(PtrWindow));
    return p;
}
SDL_PropertiesID Window::GetProperties() const
{
    return SDL_GetWindowProperties(RefThis.Get());
}
void Window::SetPosition(const SDL_Point &p)
{
    if (!SDL_SetWindowPosition(RefThis.Get(), p.x, p.y))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::SetKeyboardGrab(Bool bGrabbed)
{
    if (!SDL_SetWindowKeyboardGrab(RefThis.Get(), bGrabbed))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Maximize()
{
    if (!SDL_MaximizeWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Minimize()
{
    if (!SDL_MinimizeWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::SetResizable(Bool bResizable)
{
    if (!SDL_SetWindowResizable(RefThis.Get(), bResizable))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Show()
{
    if (!SDL_ShowWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Hide()
{
    if (!SDL_HideWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::SetFocusable(Bool bGrabbed)
{
    if (!SDL_SetWindowFocusable(RefThis.Get(), bGrabbed))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Raise()
{
    if (!SDL_RaiseWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::SetTitle(std::string_view svTitle)
{
    if (!SDL_SetWindowTitle(RefThis.Get(), svTitle.data()))
        throw Error::SDLException(NameOf(PtrWindow));
}
void Window::Restore()
{
    if (!SDL_RestoreWindow(RefThis.Get()))
        throw Error::SDLException(NameOf(PtrWindow));
}
} // namespace OpenGame::SDL3

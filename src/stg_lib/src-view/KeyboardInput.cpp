#include "og.hpp"
namespace open_stg::view_h
{
void KeyboardInputEvent::HandleEvent(const SDL_Event &e)
{
    if (e.type == (Uint32)m_kbiInformation && m_scCode == e.key.scancode)
    {
        m_fCallBack();
    }
    else if (m_kbiInformation == KeyboardInputInformation::CHECK_STATUS)
    {
        auto keyboardStateArray = SDL_GetKeyboardState(NULL);
        if (keyboardStateArray[m_scCode])
        {
            m_fCallBack();
        }
    }
}
KeyboardInputEvent::KeyboardInputEvent(SDL_Scancode sc, std::string_view sv, CallBack fkb, KeyboardInputInformation i)
{
    m_kbiInformation = i;
    m_sKeyboardBindingId = std::string{sv};
    m_fCallBack = fkb;
    m_scCode = sc;
}
std::string KeyboardInputEvent::GetKeyName() const
{
    return std::string(SDL_GetScancodeName(m_scCode));
}
const std::string &KeyboardInputEvent::GetKeyboardBindingName() const noexcept
{
    return m_sKeyboardBindingId;
}
SDL_Scancode KeyboardInputEvent::GetKey() const noexcept
{
    return m_scCode;
}
void KeyboardInputEvent::SetKey(SDL_Scancode sc) noexcept
{
    m_scCode = sc;
}
} // namespace open_stg::view_h
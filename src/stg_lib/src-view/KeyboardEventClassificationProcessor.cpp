#include "og_view.hpp"

namespace OpenGame::View
{
Static Inline std::shared_ptr<KeyBindingEventArgs> SDLKeyboardEventToEventArg(Const SDL_KeyboardEvent &e)
{
    VAR spkea = std::make_shared<KeyboardEventArgs>();
    spkea->WindowId = e.windowID;
    spkea->Type = (KeyboardEventType)e.type;
    spkea->Scancode = e.scancode;
    spkea->KeyboardState = SDL_GetKeyboardState(NullPtr);
    spkea->IsDown = e.down;
    Return std::dynamic_pointer_cast<KeyBindingEventArgs>(spkea);
}
KeyboardEventClassificationProcessor::KeyboardEventClassificationProcessor()
{
    Int iKeyEventPoolSize{0};
    m_sKeyEventPoolSize = StaticCast<size_t>(iKeyEventPoolSize);
}
Void KeyboardEventClassificationProcessor::ProcessKeyboardButtonEvent(SDL_WindowID wid, Const SDL_KeyboardEvent &e)
{
}
} // namespace OpenGame::View
#include "og_view.hpp"
namespace OpenGame::View
{
EventClassificationProcessor::EventClassificationProcessor() : m_opEventPool()
{
}
Static Inline std::shared_ptr<KeyBindingEventArgs> SDLMouseButtonEventToEventArg(Const SDL_MouseButtonEvent &e)
{
    VAR spmcea = std::make_shared<MouseClickEventArgs>();
    spmcea->Location = {e.x, e.y};
    spmcea->Clicks = e.clicks;
    spmcea->MosueId = e.which;
    spmcea->IsDown = e.down;
    Return std::dynamic_pointer_cast<KeyBindingEventArgs>(spmcea);
}
Void EventClassificationProcessor::ClassifyAndProcessEvents(SDL_WindowID wid)
{
    SDL_Event e{};
    While(SDL_PollEvent(&e))
    {
        std::shared_ptr<KeyBindingEventArgs> spEventArgs{};
        Switch(e.type)
        {
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP: {
            m_kecpKeyboardEvent.ProcessKeyboardButtonEvent(wid, e.key);
            Break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            
            Break;
        }
        }
    }
}
} // namespace OpenGame::View
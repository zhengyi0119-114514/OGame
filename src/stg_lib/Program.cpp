#include "og.hpp"
namespace OpenGame
{
    Void Program::EnterMainLoop()
    {
        m_c.Init();
        Bool bContinue = true;
        While(bContinue)
        {
            SDL_Event e;
            While(SDL_PollEvent(&e))
            {
                Switch(e.type)
                {
                case SDL_EVENT_KEY_DOWN:
                case SDL_EVENT_KEY_UP: {
                    Break;
                }
                }
            }
            m_spGameScreen->DoOperator();
            m_c.WaitToClockRing();
        }
    }
}
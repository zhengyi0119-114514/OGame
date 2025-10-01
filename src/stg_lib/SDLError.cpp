#include "og.hpp"
#include <format>
namespace OpenGame::Error
{
SDLException::SDLException(std::string_view svFunction)
{
    m_sMessage = std::format("SDL Function {:} has exception,message :{:}",svFunction,SDL_GetError());
}
const char* SDLException::what() const noexcept
{
    return m_sMessage.data();
}
} // namespace OpenGame::Error
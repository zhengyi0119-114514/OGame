#include "og_error_h.hpp"
namespace OpenGame::Error
{
RunAsRootAtException::RunAsRootAtException()
{
    m_message ="RunAsRoot";
}
const char * RunAsRootAtException::what() const noexcept
{
    return m_message.c_str();
}
}
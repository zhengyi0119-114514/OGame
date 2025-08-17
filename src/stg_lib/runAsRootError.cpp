#include "og_error_h.hpp"
namespace open_stg::error_h
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
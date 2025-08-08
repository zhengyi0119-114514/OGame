#include "og_error_h.hpp"
namespace open_stg::error_h
{
run_as_root_error::run_as_root_error()
{
    m_message ="RunAsRoot";
}
const char * run_as_root_error::what() const noexcept
{
    return m_message.c_str();
}
}
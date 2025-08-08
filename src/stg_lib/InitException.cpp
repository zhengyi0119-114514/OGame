#include "og.hpp"
#include <format>
namespace open_stg::error_h
{
InitException::InitException(std::string_view svModule, std::string_view svReason)
{
    m_message = std::format("Module :{:} init fail, {:}", svModule, svReason);
}
const char *InitException::what() const noexcept
{
    return m_message.c_str();
}
} // namespace open_stg::error_h
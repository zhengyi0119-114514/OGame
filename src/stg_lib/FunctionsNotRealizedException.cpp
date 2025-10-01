#include "og.hpp"
#include <format>
namespace OpenGame::Error
{
FunctionsNotRealizedException::FunctionsNotRealizedException(std::string_view svFunction) : m_sFunction{std::format("function {:} is not realized",svFunction)}
{
}
const char *FunctionsNotRealizedException::what() const noexcept
{
    return m_sFunction.c_str();
}
} // namespace OpenGame::Error
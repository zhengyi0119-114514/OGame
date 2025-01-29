#pragma once
#include <cstdint>
#include <format>
#include <spdlog/spdlog.h>
#include <string>
#include <string_view>
namespace OGame::Errors
{
using ErrorType = uint32_t;
class OGameError
{
  public:
    OGameError(std::string_view message, ErrorType type) : m_Message(message), m_Type(type)
    {
    }
    virtual std::string ErrorMessage() const
    {
        return this->m_Message;
    }
    virtual std::string ToString() const
    {
        return std::format("Error:{:} ,type : {:} ", m_Message, m_Type);
    }
    ErrorType ErrorCode() const
    {
        return this->m_Type;
    }

  private:
    std::string m_Message;
    const ErrorType m_Type;
};
} // namespace OGame::Errors
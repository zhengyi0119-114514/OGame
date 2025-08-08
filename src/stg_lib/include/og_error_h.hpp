#ifndef OPEN_STG_LIB_ERROR_H
#define OPEN_STG_LIB_ERROR_H
#include <exception>
#include <stdint.h>
#include <string>
#include <string_view>

namespace open_stg::error_h
{
inline constexpr const static uint32_t invalid_id = 1'145'141'919;
class run_as_root_error : public std::exception
{
  private:
    std::string m_message;

  public:
    explicit run_as_root_error();
    virtual const char *what() const noexcept override;
};
class InitException : std::exception
{
  private:
    std::string m_message;
  public:
    explicit InitException(std::string_view svModule,std::string_view svReason);
    virtual const char *what() const noexcept override;
};
} // namespace open_stg::error_h
#endif // !OPEN_STG_LIB_ERROR_H

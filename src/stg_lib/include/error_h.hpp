#ifndef OPEN_STG_LIB_ERROR_H
#define OPEN_STG_LIB_ERROR_H
#include <exception>
#include <string>
#include <string_view>
namespace open_stg::error_h
{
class name_exist_error : std::exception
{
  public:
    explicit name_exist_error(std::string_view name);
    virtual const char *what() const noexcept override;
    std::string_view get_name() const;
  private:
    std::string m_message{};
    std::string m_name{};
};
class name_not_exist_error : std::exception
{
  public:
    explicit name_not_exist_error(std::string_view name);
    virtual const char *what() const noexcept override;
    std::string_view get_name() const;

  private:
    std::string m_message{};
    std::string m_name{};
};
}
#endif // !OPEN_STG_LIB_ERROR_H

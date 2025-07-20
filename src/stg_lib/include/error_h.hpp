#ifndef OPEN_STG_LIB_ERROR_H
#define OPEN_STG_LIB_ERROR_H
#include <exception>
#include <stdint.h>
#include <string>
#include <string_view>

namespace open_stg::error_h
{
constexpr const static inline uint32_t invalid_id = 1'145'141'919;
class name_error : public std::exception
{
  public:
    virtual const char *what() const noexcept override = 0;

  protected:
    std::string m_message{};
    std::string m_name{};
};
class name_exist_error : public name_error
{
  public:
    explicit name_exist_error(std::string_view name);
    virtual const char *what() const noexcept override;
    std::string_view get_name() const;
    private:

  private:
};
class name_not_exist_error : public name_error
{
  public:
    explicit name_not_exist_error(std::string_view name);
    virtual const char *what() const noexcept override;
    std::string_view get_name() const;
};
} // namespace open_stg::error_h
#endif // !OPEN_STG_LIB_ERROR_H

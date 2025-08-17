/**
 * @file og_error_h.hpp
 * @author 9110iygnehz
 * @brief Error handling and exceptions[错误处理和异常]
 * @version 0.1
 * @date 2025-08-10
 * 
 * Contains:
 * - Exception classes[异常类]
 * - Error codes[错误码]
 */
#ifndef OPEN_STG_LIB_ERROR_H
#define OPEN_STG_LIB_ERROR_H
#include <exception>
#include <stdint.h>
#include <string>
#include <string_view>

namespace open_stg::error_h
{
inline constexpr const static uint32_t invalid_id = 1'145'141'919; ///< Invalid ID constant[无效ID常量]
/**
 * @brief Exception for running as root[以root身份运行的异常]
 */
class RunAsRootAtException : public std::exception
{
  private:
    std::string m_message; ///< Error message[错误信息]

  public:
    /**
     * @brief Construct a new Run As Root At Exception object[构造RunAsRootAtException对象]
     */
    explicit RunAsRootAtException();
    
    /**
     * @brief Get error message[获取错误信息]
     * @return const char* Error message[错误信息]
     */
    virtual const char *what() const noexcept override;
};
/**
 * @brief Initialization exception[初始化异常]
 */
class InitException : std::exception
{
  private:
    std::string m_message; ///< Error message[错误信息]
    
  public:
    /**
     * @brief Construct a new Init Exception object[构造InitException对象]
     * @param svModule Module name[模块名称]
     * @param svReason Reason for failure[失败原因]
     */
    explicit InitException(std::string_view svModule,std::string_view svReason);
    
    /**
     * @brief Get error message[获取错误信息]
     * @return const char* Error message[错误信息]
     */
    virtual const char *what() const noexcept override;
};
} // namespace open_stg::error_h
#endif // !OPEN_STG_LIB_ERROR_H

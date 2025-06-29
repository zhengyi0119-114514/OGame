#include "error_h.hpp"
#include <format>
namespace open_stg::error_h
{
	name_exist_error::name_exist_error(std::string_view name)
	{
        m_name = std::string{name};
        m_message = std::format(R"sb-(Name "{:}" exist!)sb-",name);
    }
    const char* name_exist_error::what() const noexcept
    {
        return m_message.c_str();
    }
    std::string_view name_exist_error::get_name() const
    {
        return std::string_view{m_name};
    }
    open_stg::error_h::name_not_exist_error::name_not_exist_error(std::string_view name)
    {
        m_name = name;
        m_message = std::format(R"-rc-(Name "{:}" not exist!)-rc-",name);
    }
    const char *name_not_exist_error::what() const noexcept
    {
        return m_message.c_str();
    }
    std::string_view name_not_exist_error::get_name() const
    {
        return m_name;
    }
    }
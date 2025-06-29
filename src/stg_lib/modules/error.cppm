module;
#include "error_h.hpp"
export module open_stg.error;
export namespace open_stg::error
{
	using name_exist_error = ::open_stg::error_h::name_exist_error;
	using name_not_exist_error = ::open_stg::error_h::name_not_exist_error;
}


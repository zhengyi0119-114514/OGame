module;
#include "options.hpp"
export module open_stg.opt;
namespace open_stg::opt
{
std::filesystem::path get_program_option_path()
{
    return open_stg::opt_h::get_program_option_path();
}
using image_resource_pool = open_stg::opt_h::image_resource_pool;
} // namespace open_stg::opt
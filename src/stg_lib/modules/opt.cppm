module;
#include "og_opt_h.hpp"
export module open_stg.opt;
namespace open_stg::opt
{
std::filesystem::path get_program_option_path()
{
    return open_stg::opt_h::GetProgramOptionFileDirectory();
}
} // namespace open_stg::opt